#include "texturemanager.h"

namespace muon {
	namespace graphics {

	    TextureManager* TextureManager::_instance = NULL;

		TextureManager::TextureManager()
		{
#ifdef FREEIMAGE_LIB
			FreeImage_Initialise();
#endif
		}

		TextureManager::~TextureManager()
		{
#ifdef FREEIMAGE_LIB
			FreeImage_DeInitialise();
#endif
		}

		Texture* TextureManager::loadTexture(
			std::string textureName,
			const char* path,
			TextureType type,
			GLenum filtering,
			GLint level,
			GLint border)
		{

			//image format
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			//pointer to the image, once loaded
			FIBITMAP *dib(0);
			//pointer to the image data
			BYTE* bits(0);
			//image width and height
			uint32 width(0), height(0);
			//OpenGL's image ID to map to
			GLuint gl_texID = 0;

			//check the file signature and deduce its format
			fif = FreeImage_GetFileType(path, 0);
			//if still unknown, try to guess the file format from the file extension
			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(path);
			//if still unkown, return failure
			if (fif == FIF_UNKNOWN) {
				ERR("Could not load texture: Image format not recognised.");
				return NULL;
			}

			//check that the plugin has reading capabilities and load the file
			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, path);
			else
				ERR("Could not load texture: Image format not supported.");

			//if the image failed to load, return failure
			if (!dib) {
				ERR("Could not load texture: Image failed to load.");
				return NULL;
			}

			//FreeImage_FlipVertical(dib);

			//retrieve the image data
			bits = FreeImage_GetBits(dib);
			//get the image width and height
			width = FreeImage_GetWidth(dib);
			height = FreeImage_GetHeight(dib);
			//INFO(width << "x" << height);
			uint32 bpp = FreeImage_GetBPP(dib) / 8;
			//if this somehow one of these failed (they shouldn't), return failure
			if ((bits == 0) || (width == 0) || (height == 0)) {
				ERR("Could not load texture: Invalid image.");
				return NULL;
			}

			//if this texture ID is in use, unload the current texture
			if (_textures[textureName] != NULL) _textures.erase(textureName);

			//generate an OpenGL texture ID for this texture
			glGenTextures(1, &gl_texID);
			//store the texture ID mapping
			_textures[textureName] = new Texture(path, gl_texID, width, height, type);
			//bind to the new texture ID
			glBindTexture(GL_TEXTURE_2D, gl_texID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);

			//store the texture data for OpenGL use
            glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, width, height,
				border, bpp == 4 ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, bits); //TODO: auto-detect format

			//Free FreeImage's copy of the data
			FreeImage_Unload(dib);

			return _textures[textureName];
		}

		Texture * TextureManager::loadTexture(const char * path, TextureType type, GLenum filtering, GLint level, GLint border)
		{
			return loadTexture(path, path, type, filtering, level, border);
		}

		bool TextureManager::bindTexture(std::string textureName)
		{
			//if this texture ID mapped, bind it's texture as current
			if (_textures[textureName] != NULL)
				_textures[textureName]->bind();
			else{
				ERR("Could not bind texture: Not found.");
				return false;
			}

			return true;
		}

		void TextureManager::unbindTexture()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		bool TextureManager::unloadTexture(std::string textureName)
		{
			bool result(true);
            //if this texture ID mapped, unload it's texture, and remove it from the
			if (_textures[textureName] != NULL)
			{
				_textures.erase(textureName);
			}
			else
			{
				ERR("Could not unload texture");
				result = false;
			}

			return result;
		}

		void TextureManager::unloadAllTextures()
		{

			if (_textures.size() == 0) return;

            //start at the begginning of the texture
            auto i = _textures.begin();

			//Unload the textures untill the end of the texture map is found

			while(i != _textures.end())
			{
				delete i->second;
				if(i != _textures.end()) i++;
			}

			_textures.clear();


		}

		Texture * TextureManager::getTexture(std::string textureName)
		{
			return _textures[textureName];
		}

		TextureManager& TextureManager::instance()
		{
            if(_instance == NULL) _instance = new TextureManager();
            return *_instance;
		}
	}
}
