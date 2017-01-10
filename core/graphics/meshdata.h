#ifndef MESHDATA_H
#define MESHDATA_H

#include "buffer/buffer.h"
#include "buffer/vertexarray.h"

namespace muon {
namespace graphics {

	enum MeshAttributes { //TODO: replace with bit flags
		ONLY_VERTICES,
		VERTICES_UV,
		VERTICES_UV_NORMALS
	};

	class MeshData
	{
	public:
		MeshData(GLfloat* vertexData, GLsizei vetexArraySize, GLuint* indices, GLsizei indexArraySize, MeshAttributes attribs = MeshAttributes::ONLY_VERTICES);
		~MeshData();

		void drawElements();

		inline int getIndexCount() const { return _indexCount; }
		inline MeshAttributes getAttributeTypes() const { return _attribs; }

	private:
		VertexArray* _vao;
		Buffer* _vbo;
		Buffer* _ebo;
		int _indexCount;
		MeshAttributes _attribs;
	};


}
}

#endif // !MESHDATA_H
