#include "group.h"


namespace muon {
	namespace graphics {
		Group::Group()
		{
			matrix.setIdentity();
		}

		Group::Group(math::Mat4 mat)
			: matrix(mat)
		{
		}

		Group::~Group()
		{
			for (Renderable2D* r : _children)
				delete r;
		}

		void Group::add(Renderable2D * child)
		{
			_children.push_back(child);
		}

		void Group::submit(Renderer2D* renderer) const
		{
			renderer->pushMatrix(matrix);
			for (Renderable2D* r : _children)
				r->submit(renderer);
			renderer->popMatrix();
		}


	}
}