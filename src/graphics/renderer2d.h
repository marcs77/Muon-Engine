#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <vector>
#include "renderable2d.h"
#include "../math/mat4.h"
#include "text/label.h"

namespace muon {
	namespace graphics {

		class Renderable2D;
		class Label;

		class Renderer2D {
			
		protected:
			std::vector<math::Mat4> _transformationStack;
			math::Mat4* _back;
			Renderer2D();
		public:

			void pushMatrix(math::Mat4 mat, bool overrideM = false);
			void popMatrix();

			math::Mat4* getMatrix();

			virtual void begin() {}
			virtual void submit(const Renderable2D& renderable) = 0;
			virtual void submitLabel(const Label& renderable) = 0;
			virtual void flush() = 0;
			virtual void end() {}
		};
	}
}

#endif // !RENDERER2D_H
