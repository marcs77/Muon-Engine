#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "../util/log.h"
#include "texture.h"
#include <FreeImage.h>
#include <string>
#include <map>
#include <glad/glad.h>

namespace muon {
	namespace graphics {
		class TextureManager {
		public:

			TextureManager();
			~TextureManager();

			Texture* loadTexture(
				const char* path,
				std::string textureName,		
				GLint level = 0,					
				GLint border = 0);

			bool bindTexture(std::string textureName);
			void unbindTexture();

			bool unloadTexture(std::string textureName);
			void unloadAllTextures();

			Texture* getTexture(std::string textureName);

		private:
			std::map<std::string, Texture*> _textures;
		};
	}
}

#endif // !TEXTURE_MANAGER_H
