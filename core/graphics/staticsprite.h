#ifndef STATICSPRITE_H
#define STATICSPRITE_H

#include "renderable2d.h"

namespace muon {
	namespace graphics {
		class StaticSprite : public Renderable2D
		{
		protected:

			VertexArray* _vertexArray;
			IndexBuffer* _indexBuffer;

			Shader& _shader;

		public:

			StaticSprite(math::Vec3f pos, math::Vec2f size, math::Vec4f color, Shader& shader);
            ~StaticSprite()
			{
				delete _vertexArray;
				delete _indexBuffer;
			}

			inline Shader& getShader() const { return _shader; }

			inline const VertexArray* getVAO() const { return _vertexArray; }
			inline const IndexBuffer* getIBO() const { return _indexBuffer; }
		};
	}
}

#endif // !STATICSPRITE_H
