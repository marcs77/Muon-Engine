#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "buffer.h"
#include <glad/glad.h>
#include <vector>

namespace muon {
	namespace graphics {
		class VertexArray {
		private:
			GLuint _arrayId;
		public:
			VertexArray();
			~VertexArray();

            void addVertexAttributePointer(Buffer* buffer, GLuint location, GLint attributeSize, GLenum type,
                                           GLboolean normalized, GLsizei stride, const GLvoid* offset);

            inline GLuint getId() const { return _arrayId; }

            static VertexArray* currentlyBoundVAO;
            static void bind(VertexArray* vao);
            static void unbind();
		};
	}
}

#endif // !VERTEXARRAY_H
