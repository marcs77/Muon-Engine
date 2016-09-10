#include "renderer2d.h"

namespace muon {
	namespace graphics {
		Renderer2D::Renderer2D()
		{
			_transformationStack.push_back(math::Mat4::identity());
			_back = &_transformationStack.back();
		}

		void Renderer2D::pushMatrix(math::Mat4 mat, bool overrideM)
		{
			_transformationStack.push_back(overrideM ? mat : _transformationStack.back() * mat);
			_back = &_transformationStack.back();
		}

		void Renderer2D::popMatrix()
		{
			if (_transformationStack.size() > 1)
				_transformationStack.pop_back();
			_back = &_transformationStack.back();
		}
		math::Mat4 * Renderer2D::getMatrix()
		{
			return _back;
		}
	}
}
