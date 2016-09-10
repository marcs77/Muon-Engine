#include "sprite.h"

namespace muon {
	namespace graphics {

		Sprite::Sprite(float x, float y, float w, float h, const math::Vec4f color, Texture* tex, math::Vec2f anchor)
			: Renderable2D(math::Vec3f(x, y, 0), math::Vec2f(w, h), color, tex, anchor)
		{

		}

	}
}