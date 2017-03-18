#ifndef BATCHRENDERER2D_H
#define BATCHRENDERER2D_H

#include "../math/vec2.h"
#include "../math/mat4.h"
#include "../util/color.h"
#include "buffer/vertexarray.h"
#include "buffer/buffer.h"
#include "texture.h"
#include "shader/shader.h"

namespace muon {
namespace graphics {

	struct Vertex2D
	{
		math::Vec2f pos; //TODO: Make Vec3f to enable depth
		math::Vec2f uv;
		Color color;
		short textureSlot;
	};

#define BATCHRENDERER_MAX_SPRITES 20000
#define BATCHRENDERER_VERTEX_SIZE sizeof(Vertex2D)
#define BATCHRENDERER_SPRITE_SIZE BATCHRENDERER_VERTEX_SIZE * 4
#define BATCHRENDERER_BUFFER_SIZE BATCHRENDERER_SPRITE_SIZE * BATCHRENDERER_MAX_SPRITES
#define BATCHRENDERER_INDICES_SIZE BATCHRENDERER_MAX_SPRITES * 6
#define BATCHRENDERER_MAX_TEXTURES_PER_BATCH 32

	struct Renderable2D
	{
		Vertex2D vertices[4];
		//TODO: Should the struct contain the transformation matrix?
	};

	struct Sprite
	{
		math::Vec2f position;
		math::Vec2f size;
		math::Vec2f anchor; //Values from 0 to 1
		math::Vec2f uvs[4] = { {0,0}, {0,1}, {1,1}, {1,0} };
		float rotation; //TODO: Implement, or use matrices
		Texture* texture;
		Color color = Color(COL_WHITE);

		Sprite(Texture* texture, math::Vec2f position, math::Vec2f size);
		Sprite(Color color, math::Vec2f position, math::Vec2f size);
	};

	

	class BatchRenderer2D {
	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		void begin();

		void submit(const Renderable2D& renderer);
		void submit(const Sprite& sprite);

		void end();
		void flush();

		inline void setProjectionMatrix(const math::Mat4& mat) { _projectionMatrix = mat; }

	private:
		Shader batchShader;

		VertexArray* _vao;
		Buffer* _vbo;
		Buffer* _ebo;

		Vertex2D* _buffer;
		GLuint _textures[BATCHRENDERER_MAX_TEXTURES_PER_BATCH] = {0}; //Temporal array, reset with every batch
		int usedTextures = 0;

		math::Mat4 _projectionMatrix;
		short _indexCount;

		Renderable2D createRenderable2D(const Sprite& sprite);

		short getTextureSlot(GLuint texture);


	};
}
}

#endif // !BATCHRENDERER2D_H
