#ifndef GROUP_H
#define GROUP_H

#include "../renderable2d.h"
#include "../renderer2d.h"
#include <vector>
#include "../../math/mat4.h"
#include "../../math/vec2.h"

namespace muon {
	namespace graphics {
		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> _children;
		public:

			math::Mat4 matrix;

			Group();
			Group(math::Mat4 mat);
			~Group();

			void add(Renderable2D* child);
			void submit(Renderer2D* renderer) const override;
		};
	}
}

#endif // !GROUP_H