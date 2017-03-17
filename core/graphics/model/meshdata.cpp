#include "meshdata.h"
#include "../../util/log.h"
namespace muon {
namespace graphics {
	MeshData::MeshData() : _vao(NULL), _vbo(NULL), _ebo(NULL), _indexCount(0)
	{
	}

	MeshData::MeshData(GLfloat* vertexData, GLsizei vetexArraySize, GLuint* indices, GLsizei indexArraySize, MeshAttributes attribs) :
		_vao(new VertexArray()), _vbo(new Buffer()), _ebo(new Buffer(GL_ELEMENT_ARRAY_BUFFER)),
		_indexCount(indexArraySize / sizeof(GLuint))
	{
		_vbo->load(vertexData, vetexArraySize);
		_ebo->load(indices, indexArraySize);

		VertexArray::bind(_vao);
		switch (attribs)
		{
		case VERTICES_UV_NORMALS:
			_vao->addVertexAttributePointer(_vbo, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
			_vao->addVertexAttributePointer(_vbo, 1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			_vao->addVertexAttributePointer(_vbo, 2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
			break;
		case VERTICES_UV:
			_vao->addVertexAttributePointer(_vbo, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			_vao->addVertexAttributePointer(_vbo, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			break;
		default:
			ERR("Invalid enum for MeshAttributes, using ONLY_VERTICES.");
		case ONLY_VERTICES:
			_vao->addVertexAttributePointer(_vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			break;
		
		}
		Buffer::bind(_ebo);
		VertexArray::unbind();
	}

	MeshData::MeshData(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture*> textures) :
		_vertices(vertices), _indices(indices), textures(textures),
		_vao(new VertexArray()), _vbo(new Buffer()), _ebo(new Buffer(GL_ELEMENT_ARRAY_BUFFER)), _indexCount(indices.size())
	{
		_vbo->load(vertices.data(), vertices.size() * sizeof(Vertex));
		_ebo->load(indices.data(), indices.size() * sizeof(GLuint));

		VertexArray::bind(_vao);

		_vao->addVertexAttributePointer(_vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		_vao->addVertexAttributePointer(_vbo, 1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
		_vao->addVertexAttributePointer(_vbo, 2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

		Buffer::bind(_ebo);
		VertexArray::unbind();
	}

	MeshData::~MeshData()
	{
		delete _vao;
		delete _vbo;
		delete _ebo;
	}

	void MeshData::drawElements() const
	{
		VertexArray::bind(_vao);
		glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
		VertexArray::unbind();
	}

}
}