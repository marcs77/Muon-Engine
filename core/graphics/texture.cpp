#include "texture.h"

namespace muon {
	namespace graphics {

		Texture::Texture(std::string path, GLuint id, GLsizei width, GLsizei height, TextureType type)
			: _path(path), _id(id), _width(width), _height(height), _type(type)
		{

		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &_id);
		}

		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, _id);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}