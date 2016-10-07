#include "tilelayer.h"

namespace muon {
	namespace graphics {

		TileLayer::TileLayer(Renderer2D* renderer, Shader * shader)
			: Layer(renderer, shader, math::Mat4::ortho(0, 960, 0, 540, -2, 10))
		{
			
		}

		

	}
}