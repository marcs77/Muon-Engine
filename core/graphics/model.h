#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "meshdata.h"

namespace muon {
namespace graphics {
	class Model {
	public:

	private:
		std::vector<MeshData*> meshes;
	};
}
}

#endif // !MODEL_H
