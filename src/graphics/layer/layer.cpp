#include "layer.h"

namespace muon {
	namespace graphics {
		Layer::Layer(Renderer2D* renderer, Shader* shader, math::Mat4 prMatrix)
            : _renderer(renderer), _shader(shader), _prMatrix(prMatrix) /* TODO: Remove */, label("xDDdDD~Ññáèü", math::Vec2f(0,50), &audiowide)
		{
			_shader->use();
			_shader->setUniformMat4("pr_matrix", _prMatrix);
			_shader->disable();
		}
		Layer::~Layer()
		{
			delete _renderer;
			for (int i = _objects.size()-1; i >= 0; i--) {
				delete _objects[i];
			}
		}
		void Layer::add(Renderable2D * renderable)
		{
			_objects.push_back(renderable);
		}

		void Layer::render()
		{
			_shader->use();
			_renderer->begin();
			
			for (const Renderable2D* r : _objects) {
				r->submit(_renderer);
			}

			//TODO:remove
			_renderer->submitLabel(label);

			_renderer->end();
			_renderer->flush();
			_shader->disable();
		}

		
	}
}
