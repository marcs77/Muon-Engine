#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "../common.h"
#include "texture.h"
#include <FreeImage.h>
#include <string>
#include <unordered_map>
#include <glad/glad.h>

namespace muon {
	namespace graphics {
        
		class TextureManager {
		public:

			static constexpr const char* DEFAULT_TEXTURE_PATH = "resources/textures/";

            static TextureManager& instance();

			~TextureManager();

			Texture* loadTexture(
				std::string textureName,
				const char* path,
				TextureType type = DEFAULT,
				GLenum filtering = GL_LINEAR,
				GLint level = 0,
				GLint border = 0);

			Texture* loadTexture(
				const char* path,
				TextureType type = DEFAULT,
				GLenum filtering = GL_LINEAR,
				GLint level = 0,
				GLint border = 0);

			bool bindTexture(std::string textureName);
			void unbindTexture();

			bool unloadTexture(std::string textureName);
			void unloadAllTextures();

			Texture* getTexture(std::string textureName);
            
            void loadImage(FIBITMAP** bmpPointer, std::string texturePath);

		private:
            std::unordered_map<std::string, Texture*> _textures;

            TextureManager();
            static TextureManager* _instance;

		};
	}
}

#endif // !TEXTURE_MANAGER_H
