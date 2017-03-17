#ifndef STANDARD_RENDERER_H
#define STANDARD_RENDERER_H

#include "model/meshdata.h"
#include "model/model.h"
#include "shader/shader.h"

namespace muon {
namespace graphics {

	class StandardRenderer {
	public:

		StandardRenderer();

		void drawMesh(math::Mat4* modelMatrix, const MeshData* mesh) const;
		void drawModel(math::Mat4* modelMatrix, const Model* model) const;
	private:
		Shader shader;
	};

}
}

#endif // !STANDARD_RENDERER_H