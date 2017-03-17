#include "standardrenderer.h"
#include "texturemanager.h"
#include "shader/shadermanager.h"

namespace muon {
namespace graphics {

	StandardRenderer::StandardRenderer()
		: shader("resources/shaders/standardVertex.glsl", "resources/shaders/standardFragment.glsl")
	{

	}

	void StandardRenderer::drawMesh(const MeshData* mesh) const
	{
		ShaderManager::useShader(&shader);

		int diffuseN = 0;
		int specularN = 0;
		static constexpr int MAX_DIFFUSE = 3;
		static constexpr int MAX_SPECULAR = 3;

		//TODO: temporal setup
		for (int i = 0; i < mesh->textures.size(); i++) {
			if (mesh->textures[i]->getType() == SPECULAR_MAP) {
				continue;
			}
			else if(mesh->textures[i]->getType() == DIFFUSE_MAP)
			{
				if (diffuseN >= MAX_DIFFUSE) break;
				glActiveTexture(GL_TEXTURE0 + diffuseN++);
				mesh->textures[i]->bind();
			}
		}

		for (int i = 0; i < mesh->textures.size(); i++) {
			if (mesh->textures[i]->getType() == SPECULAR_MAP)
			{
				if (specularN >= MAX_SPECULAR) break;
				glActiveTexture(GL_TEXTURE0 + MAX_DIFFUSE + specularN++);
				mesh->textures[i]->bind();
			}
		}

		mesh->drawElements();

	}

	void StandardRenderer::drawModel(const Model * model) const
	{
		for (int i = 0; i < model->meshes.size(); i++)
		{
			drawMesh(&model->meshes[i]);
		}
	}


}
}