#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

namespace muon {
	namespace graphics {

		class TextureManager;

		class Texture
		{
			friend class TextureManager;
		protected:
			std::string _path;
			GLuint _id;
			GLsizei _width, _height;

			Texture(std::string path, GLuint id, GLsizei width, GLsizei height);
			~Texture();
		public:

			inline GLsizei getWidth() const { return _width; }
			inline GLsizei getHeight() const { return _height; }
			inline GLuint getId() const { return _id; }
			inline std::string getPath() const { return _path; }

			void bind() const;
			void unbind() const;

		};
	}
}

#endif // !TEXTURE_H
