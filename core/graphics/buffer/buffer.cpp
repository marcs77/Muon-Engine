#include "buffer.h"
namespace muon {
	namespace graphics {

        Buffer::Buffer(GLenum target)
            : _target(target)
		{
			glGenBuffers(1, &_bufferId);
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &_bufferId);
		}

        void Buffer::bind(Buffer* b)
		{
            glBindBuffer(b->_target, b->_bufferId);
		}

        void Buffer::unbind(GLenum target)
		{
            glBindBuffer(target, 0);
		}

        void Buffer::unbind(Buffer* b)
        {
            unbind(b->_target);
        }
		
        void Buffer::load(GLvoid *data, GLsizei size, GLenum usage)
        {
            bind(this);
            glBufferData(_target, size, data, usage);
            unbind(this);
        }

	}
}
