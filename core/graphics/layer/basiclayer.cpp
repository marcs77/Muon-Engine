#include "basiclayer.h"

namespace muon {
	namespace graphics {

		BasicLayer::BasicLayer(Renderer2D* renderer, Shader* shader, math::Mat4 prMatrix)
			: Layer(renderer, shader, prMatrix)
		{

		}
	}
}