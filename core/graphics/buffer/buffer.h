#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>

namespace muon {
	namespace graphics {
		class Buffer
		{
		public:
            Buffer(GLenum target = GL_ARRAY_BUFFER);
			~Buffer();

            void load(GLvoid* data, GLsizei size, GLenum usage = GL_STATIC_DRAW);

			inline GLuint getBufferId() const { return _bufferId; }
            inline GLenum getTarget() const { return _target; }
            //inline GLuint getCount() const { return _count; }

            static void bind(Buffer* b);
            static void unbind(GLenum target);
            static void unbind(Buffer* b);

		private:
			GLuint _bufferId;
            GLenum _target;
		};
	}
}

#endif // !BUFFER_H
