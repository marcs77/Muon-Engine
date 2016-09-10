#ifndef SIMPLERENDERER2D_H
#define SIMPLERENDERER2D_H

#include <glad/glad.h>
#include <deque>
#include "../math/mat4.h"
#include "renderer2d.h"
#include "staticsprite.h"

namespace muon {
	namespace graphics {
		class SimpleRenderer2D : public Renderer2D {

		private:
			std::deque<const StaticSprite*> _renderQueue;
			math::Mat4 translation;

		public:
			void submit(const Renderable2D& renderable) override;
			void submitLabel(const Label& label) override {}
			void flush() override;
		};
	}
}

#endif // !SIMPLERENDERER2D_H
