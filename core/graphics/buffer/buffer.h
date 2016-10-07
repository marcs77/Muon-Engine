#ifndef BUFFER_H
#define BUFFER_H

#include <glad\glad.h>

namespace muon {
	namespace graphics {
		class Buffer
		{
		public:
			Buffer(GLfloat* data, GLsizei count, GLuint compCount);
			~Buffer();

			inline GLuint getBufferId() const { return _bufferId; }
			inline GLuint getComponentCount() const { return _componentCount; }

			void bind() const;
			void unbind() const;

		private:
			GLuint _bufferId;
            GLuint _componentCount; //float or Vec2, Vec3...
		};
	}
}

#endif // !BUFFER_H
