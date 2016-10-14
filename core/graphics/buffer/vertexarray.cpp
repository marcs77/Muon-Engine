#include "vertexarray.h"

namespace muon {
	namespace graphics {

        VertexArray* VertexArray::currentlyBoundVAO = NULL;

		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &_arrayId);
		}

		VertexArray::~VertexArray() 
		{
            glDeleteVertexArrays(1, &_arrayId);
            //for (size_t i = 0; i < _buffers.size(); i++)
            //    delete _buffers[i];

		}

        void VertexArray::addVertexAttributePointer(Buffer* buffer, GLuint location, GLint attributeSize, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *offset)
        {
            Buffer::bind(buffer);
            glEnableVertexAttribArray(location);
            glVertexAttribPointer(location, attributeSize, type, normalized, stride, offset);

            //Buffer::unbind(buffer->getTarget());
        }


        void VertexArray::bind(VertexArray* vao)
		{
            if(currentlyBoundVAO != vao) {
                glBindVertexArray(vao->getId());
                currentlyBoundVAO = vao;
            }
		}

        void VertexArray::unbind()
		{
            glBindVertexArray(0);
            currentlyBoundVAO = NULL;
		}


	}
}
