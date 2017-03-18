#include "batchrenderer2d.h"
#include "shader/shadermanager.h"

namespace muon {
namespace graphics {

	BatchRenderer2D::BatchRenderer2D() :
		_vao(new VertexArray()), _vbo(new Buffer()), _ebo(new Buffer(GL_ELEMENT_ARRAY_BUFFER)),
		batchShader("resources/shaders/batchVertex.glsl", "resources/shaders/batchFragment.glsl"), _projectionMatrix(1.0f), _indexCount(0)
	{
		_vbo->load(NULL, BATCHRENDERER_BUFFER_SIZE, GL_DYNAMIC_DRAW);
		
		GLushort indices[BATCHRENDERER_INDICES_SIZE];
		GLushort offset = 0;

		for (int i = 0; i < BATCHRENDERER_INDICES_SIZE; i += 6) {
			indices[i    ] = offset    ;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset    ;

			offset += 4;
		}

		_ebo->load(indices, sizeof(indices));

		VertexArray::bind(_vao);
		Buffer::bind(_vbo);
		_vao->addVertexAttributePointer(_vbo, 0, 2, GL_FLOAT, GL_FALSE, BATCHRENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(Vertex2D, Vertex2D::pos));
		_vao->addVertexAttributePointer(_vbo, 1, 2, GL_FLOAT, GL_FALSE, BATCHRENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(Vertex2D, Vertex2D::uv));
		_vao->addVertexAttributePointer(_vbo, 2, 4, GL_FLOAT, GL_TRUE, BATCHRENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(Vertex2D, Vertex2D::color));
		_vao->addVertexAttributePointer(_vbo, 3, 1, GL_SHORT, GL_FALSE, BATCHRENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(Vertex2D, Vertex2D::textureSlot));
		
		Buffer::unbind(_vbo);
		Buffer::bind(_ebo);
		
		VertexArray::unbind();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete _vao;
		delete _vbo;
		delete _ebo;
	}

	void BatchRenderer2D::begin()
	{
		Buffer::bind(_vbo);
		_buffer = (Vertex2D*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::submit(const Renderable2D& renderable)
	{
		for (int i = 0; i < 4; i++)
		{
			*_buffer = renderable.vertices[i];
			_buffer++;
		}
		_indexCount += 6;
	}

	void BatchRenderer2D::submit(const Sprite & sprite)
	{
		submit(createRenderable2D(sprite));
	}

	void BatchRenderer2D::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer2D::flush()
	{

		ShaderManager::useShader(&batchShader);
		ShaderManager::setProjectionMatrix(_projectionMatrix);

		for (int i = 0; i < usedTextures; i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, _textures[i]);
		}


		VertexArray::bind(_vao);
		glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_SHORT, NULL);
		VertexArray::unbind();


		_indexCount = 0;

		ShaderManager::disableShader();

	}

	Renderable2D BatchRenderer2D::createRenderable2D(const Sprite & sprite)
	{
		Renderable2D result;
		math::Vec2f offset = sprite.anchor * sprite.size;
		result.vertices[0].pos = sprite.position - offset;
		result.vertices[1].pos = sprite.position - offset;
		result.vertices[1].pos.y += sprite.size.y;
		result.vertices[2].pos = sprite.position - offset + sprite.size;
		result.vertices[3].pos = sprite.position - offset;
		result.vertices[3].pos.x += sprite.size.x;

		short textureSlot = getTextureSlot(sprite.texture->getId());;

		for (int i = 0; i < 4; i++) 
		{
			result.vertices[i].uv = sprite.uvs[i];
			result.vertices[i].textureSlot = textureSlot;
			result.vertices[i].color = sprite.color;
		}

		return result;
	}

	short BatchRenderer2D::getTextureSlot(GLuint texture)
	{
		int texSlot = 0;

		if(texture > 0) 
		{
			//Search for the texture
			for (int i = 0; i < usedTextures; i++)
			{
				if (_textures[i] == texture)
				{
					return i;
				}
			}

			//If it doesn't exist
			//Check the texture limit
			if(usedTextures >= BATCHRENDERER_MAX_TEXTURES_PER_BATCH) 
			{
				end();
				flush();
				begin();
				usedTextures = 0;
			}
			
			//Add the texture
			_textures[usedTextures] = texture;
			usedTextures++;
			return usedTextures - 1;
		}

		return -1;
	}

	Sprite::Sprite(Texture * texture, math::Vec2f position, math::Vec2f size) :
		texture(texture), position(position), size(size), anchor(math::Vec2f::zero)
	{
	}

}
}
