#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "meshdata.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

namespace muon {
namespace graphics {

	using namespace Assimp;

	class Model {
		
	public:
		Model(const char* path);
		std::vector<MeshData> meshes;

		~Model();
	private:
		std::string path;

		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		MeshData processMesh(aiMesh* node, const aiScene* scene);
		std::vector<Texture*> loadMaterialTextures(aiMaterial* mat, aiTextureType matType, TextureType type);

		static std::vector<Texture*> loaded_textures;

	};
}
}

#endif // !MODEL_H
