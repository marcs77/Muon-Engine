#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <glad/glad.h>

namespace muon {
	namespace graphics {
		class IndexBuffer
		{
		public:
			IndexBuffer(GLushort* data, GLsizei count);
			~IndexBuffer();

			inline GLuint getBufferId() const { return _bufferId; }
			inline GLuint getCount() const { return _count; }

			void bind() const;
			void unbind() const;

		private:
			GLuint _bufferId;
            GLuint _count; //float or Vec2, Vec3...
		};
	}
}

#endif // !INDEXBUFFER_H
