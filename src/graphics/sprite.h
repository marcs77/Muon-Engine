#ifndef SPRITE_H
#define SPRITE_H

#include "renderable2d.h"
#include "../math/vec4.h"
#include "../math/vec2.h"

namespace muon {
	namespace graphics {
		class Sprite : public Renderable2D 
		{
		public:
            Sprite(float x, float y, float w, float h, const math::Vec4f color = math::Vec4f(1,1,1,1), Texture* tex = NULL, math::Vec2f anchor = math::Vec2f());
		};
	}
}

#endif // !SPRITE_H
