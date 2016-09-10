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
			std::vector<Buffer*> _buffers;
		public:
			VertexArray();
			~VertexArray();

			void addBuffer(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;
		};
	}
}

#endif // !VERTEXARRAY_H
