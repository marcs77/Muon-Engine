#include "layer.h"

namespace muon {
	namespace graphics {
		Layer::Layer(Renderer2D* renderer, Shader* shader, math::Mat4 prMatrix)
			: _renderer(renderer), _shader(shader), _prMatrix(prMatrix)
		{

			GLint texIDs[32];
			for (int i = 0; i < 32; i++) texIDs[i] = i;
			_shader->use();
			_shader->setUniform1iv("tex", 32, texIDs);

			_shader->use();
			_shader->setUniformMat4("pr_matrix", _prMatrix);
			_shader->disable();
		}
		Layer::~Layer()
		{
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

			_renderer->end();
			_renderer->flush();
			_shader->disable();
		}

		void Layer::submitLabel(Label* label) {
			_renderer->submitLabel(*label);
		}
		
	}
}
