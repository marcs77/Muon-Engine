#ifndef RENDERABLE2D_H
#define RENDERABLE2D_H

#include "buffer/buffers.h"
#include "renderer2d.h"
#include "shader.h"
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/vec4.h"
#include "texture.h"

namespace muon {
	namespace graphics {

		struct VertexData {
			math::Vec3f vertex;
			math::Vec2f uv;
			int tid;
			unsigned int color;
		};

		class Renderer2D;

		class Renderable2D {

		protected:
			
			math::Vec2f _size;
			math::Vec4f _color;
			math::Vec3f _position;
			math::Vec2f _uvs[4];
			math::Vec2f _anchor;
			Texture* _texture;
			
			Renderable2D();

		public:

			
			Renderable2D(math::Vec3f pos, math::Vec2f size, math::Vec4f color, Texture* texture = NULL, math::Vec2f anchor = math::Vec2f());
            virtual ~Renderable2D() {}

			virtual void submit(Renderer2D* renderer) const;

			inline const math::Vec2f& getSize() const { return _size; };
			inline const math::Vec4f& getColor() const { return _color; };
			inline const math::Vec3f& getPosition() const { return _position; };
			inline const math::Vec2f& getUV(int index) const { return _uvs[index]; };
			inline const math::Vec2f* getUVs() const { return _uvs; };
			inline const GLuint getTextureID() const { return _texture == NULL ? 0 : _texture->getId(); };
			inline const math::Vec3f getVertex(int n) const 
			{
				switch (n)
				{
				case 0: return math::Vec3f(_position.x - _anchor.x * _size.x, _position.y - _anchor.y * _size.y, _position.z);
				case 1: return math::Vec3f(_position.x - _anchor.x * _size.x, _position.y + _size.y - _anchor.y * _size.y, _position.z);
				case 2: return math::Vec3f(_position.x + _size.x - _anchor.x * _size.x, _position.y + _size.y - _anchor.y * _size.y, _position.z);
				case 3: return math::Vec3f(_position.x + _size.x - _anchor.x * _size.x, _position.y - _anchor.y * _size.y, _position.z);

				default:
					return math::Vec3f();
				}
			}

			inline math::Vec3f* position() { return &_position; };
		private:
			void defaultUVs();
		
		};
	}
}

#endif // !RENDERABLE2D_H
