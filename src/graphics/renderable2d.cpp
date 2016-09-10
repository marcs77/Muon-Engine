#include "renderable2d.h"

namespace muon {
	namespace graphics {
		Renderable2D::Renderable2D()
		{
			defaultUVs();
		}

		Renderable2D::Renderable2D(math::Vec3f pos, math::Vec2f size, math::Vec4f color, Texture* texture, math::Vec2f anchor)
			: _position(pos), _size(size), _color(color), _texture(texture), _anchor(anchor)
		{
			defaultUVs();
		}

		void Renderable2D::submit(Renderer2D * renderer) const
		{
			renderer->submit(*this);
		}

		void Renderable2D::defaultUVs()
		{
			_uvs[0] = math::Vec2f(0, 0);
			_uvs[1] = math::Vec2f(0, 1);
			_uvs[2] = math::Vec2f(1, 1);
			_uvs[3] = math::Vec2f(1, 0);
		}

		

	}
}