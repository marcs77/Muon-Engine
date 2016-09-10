#include "tilelayer.h"

namespace muon {
	namespace graphics {

		TileLayer::TileLayer(Shader * shader)
			: Layer(new BatchRenderer2D(), shader, math::Mat4::ortho(0, 960, 540, 0, -2, 10))
		{
			GLint texIDs[32];
			for (int i = 0; i < 32; i++) texIDs[i] = i;
			shader->use();
			shader->setUniform1iv("tex", 32, texIDs);
		}

		

	}
}