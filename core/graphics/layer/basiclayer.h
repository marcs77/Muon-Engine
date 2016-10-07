#ifndef BASICLAYER_H
#define BASICLAYER_H

#include "layer.h"
#include "../batchrenderer2d.h"
#include "../../math/mat4.h"

namespace muon {
namespace graphics {

	class BasicLayer : public Layer
	{
	public:
		BasicLayer(Renderer2D* renderer, Shader* shader, math::Mat4 prMatrix);
	};

}
}

#endif // !BASICLAYER_H
