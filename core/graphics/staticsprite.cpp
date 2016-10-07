#include "staticsprite.h"

namespace muon {
	namespace graphics {

		StaticSprite::StaticSprite(math::Vec3f pos, math::Vec2f size, math::Vec4f color, Shader& shader)
			: Renderable2D(pos, size, color), _shader(shader)
		{
			_vertexArray = new VertexArray();

			GLfloat verts[] = {
				0, 0, 0,
				0, size.y, 0,
				size.x, size.y, 0,
				size.x, 0, 0,
			};

			GLfloat colors[] = {
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
			};

			GLushort indices[] = {
				0, 1, 2,
				2, 3, 0
			};

			_vertexArray->addBuffer(new Buffer(verts, 12, 3), 0);
			_vertexArray->addBuffer(new Buffer(colors, 16, 4), 1);

			_indexBuffer = new IndexBuffer(indices, 6);
		}



	}
}