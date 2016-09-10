#ifndef LAYER_H
#define LAYER_H

#include "../renderable2d.h"
#include "../renderer2d.h"
#include "../../math/mat4.h"
#include "../text/font.h"
#include "../text/label.h"

//TODO: Remove
#include "../sprite.h"

namespace muon {
	namespace graphics {
		class Layer {
		protected:
			Renderer2D* _renderer;
			std::vector<Renderable2D*> _objects;
			Shader* _shader;
			math::Mat4 _prMatrix;
			//TODO: remove
			Font audiowide;
			Label label;

			Layer(Renderer2D* renderer, Shader* shader, math::Mat4 prMatrix);
		public:
			virtual ~Layer();
			
			virtual void add(Renderable2D* renderable);
			virtual void render();

		};
	}
}

#endif // !LAYER_H
