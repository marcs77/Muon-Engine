#include "buffer.h"
namespace muon {
	namespace graphics {
		Buffer::Buffer(GLfloat * data, GLsizei count, GLuint compCount) 
			: _componentCount(compCount)
		{
			glGenBuffers(1, &_bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &_bufferId);
		}

		void Buffer::bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
		}

		void Buffer::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		
	}
}
