#ifndef TILELAYER_H
#define TILELAYER_H

#include "layer.h"
#include "../batchrenderer2d.h"
#include "../../math/mat4.h"

namespace muon { namespace graphics {

	class TileLayer : public Layer 
	{
	public:
		TileLayer(Shader* shader);
		//~TileLayer();
	};

} }

#endif // !TILELAYER_H