#include "model.h"
#include "../../util/log.h"
#include "../texturemanager.h"
#include "../../util/fileutils.h"

namespace muon {
namespace graphics { 

	std::vector<Texture*> Model::loaded_textures;

	Model::Model(const char* path)
	{
		loadModel(path);
	}

	void Model::loadModel(std::string path)
	{
		
		loaded_textures.clear();

		Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			ERR("Assimp failed to load model: " << path);
			ERR("Error: " << importer.GetErrorString());
			return;
		}

		this->path = path;
		processNode(scene->mRootNode, scene);
	}

	void Model::processNode(aiNode * node, const aiScene * scene)
	{
		for (int i = 0; i < node->mNumMeshes; i++) 
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}

		for (int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	MeshData Model::processMesh(aiMesh * mesh, const aiScene * scene)
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture*> textures;

		//Vertices
		for (int i = 0; i < mesh->mNumVertices; i++) 
		{
			Vertex vertex;
			math::Vec3f temp;
			temp.x = mesh->mVertices[i].x;
			temp.y = mesh->mVertices[i].y;
			temp.z = mesh->mVertices[i].z;

			vertex.position = temp;

			if (mesh->mNormals) {
				temp.x = mesh->mNormals[i].x;
				temp.y = mesh->mNormals[i].y;
				temp.z = mesh->mNormals[i].z;

				vertex.normal = temp;
			}

			if (mesh->mTextureCoords[0])
			{
				math::Vec2f uv;
				uv.x = mesh->mTextureCoords[0][i].x;
				uv.y = mesh->mTextureCoords[0][i].y;

				vertex.uv = uv;
			}
				

			vertices.push_back(vertex);
		}

		//Indices
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		//Materials
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture*> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, DIFFUSE_MAP);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture*> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, SPECULAR_MAP);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return MeshData(vertices, indices, textures);
	}

	std::vector<Texture*> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType matType, TextureType type)
	{
		std::vector<Texture*> textures;

		for (int i = 0; i < mat->GetTextureCount(matType); i++)
		{
			aiString str;
			mat->GetTexture(matType, i, &str);
			bool skip = false;

			for (int j = 0; j < loaded_textures.size(); j++) {
				if (strcmp(loaded_textures[j]->getPath().c_str(), str.C_Str())) {
					textures.push_back(loaded_textures[j]);
					skip = true;
					break;
				};
			}

			if (!skip)
			{
				//TODO: Check if the file is null
				std::string relPath = std::string(str.C_Str());
				Texture *t = TextureManager::instance().loadTexture((get_directory(path) + relPath).c_str(), type);
				textures.push_back(t);
			}

		}

		return textures;
	}

	Model::~Model() 
	{
		for (int i = 0; i < meshes.size(); i++) 
		{
			meshes.at(i).disposeBuffers();
		}
	}

}
}


