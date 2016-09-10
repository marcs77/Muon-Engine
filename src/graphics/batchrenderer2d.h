#ifndef BATCHRENDERER2D_H
#define BATCHRENDERER2D_H

#include "renderer2d.h"
#include "buffer/indexbuffer.h"
#include "../util/color.h"
#include <vector>
#include "../math/mat4.h"

//#include "../math/lingeom.h"

namespace muon {
	namespace graphics {

#define RENDERER_MAX_SPRITES 20000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6
#define SHADER_VERTEX_INDEX 0		
#define SHADER_UV_INDEX 1		
#define SHADER_TID_INDEX 2		
#define SHADER_COLOR_INDEX 3	

		class BatchRenderer2D : public Renderer2D {
		public:

			BatchRenderer2D();
			~BatchRenderer2D();

			void begin();

			void submit(const Renderable2D& renderable) override;

			void end();
			void flush() override;

			int getTextureSlot(const GLuint tid);
			void submitLabel(const Label& label) override;
		private:
			GLuint _vao;
			IndexBuffer* _ibo;
			GLsizei _indexCount;
			GLuint _vbo;
			VertexData* _buffer;
			std::vector<GLuint> _textureSlots;
		};
	}
}


#endif // !BATCHRENDERER2D_H
