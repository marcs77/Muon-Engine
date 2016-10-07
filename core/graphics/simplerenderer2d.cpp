#include "simplerenderer2d.h"

namespace muon {
	namespace graphics {

		void SimpleRenderer2D::submit(const Renderable2D& renderable)
		{
			_renderQueue.push_back(&(StaticSprite&)renderable);
		}

		void SimpleRenderer2D::flush()
		{
			while (!_renderQueue.empty()) {
				const StaticSprite& r = *_renderQueue.front();
				
				r.getVAO()->bind();
				r.getIBO()->bind();
				translation.setIdentity();
				translation.setTranslation(r.getPosition());
				r.getShader().setUniformMat4("ml_matrix", translation);
				glDrawElements(GL_TRIANGLES, r.getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);
				
				r.getIBO()->unbind();
				r.getVAO()->unbind();

				_renderQueue.pop_front();
			}
		}

		

	}
}