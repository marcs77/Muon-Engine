#ifndef MESHDATA_H
#define MESHDATA_H

#include "../../common.h"
#include "../../math/vec3.h"
#include "../buffer/buffer.h"
#include "../buffer/vertexarray.h"
#include "../texture.h"
#include <vector>

namespace muon {
namespace graphics {

	struct Vertex {
		math::Vec3f position;
		math::Vec2f uv;
		math::Vec3f normal;
	};

	enum MeshAttributes { //TODO: replace with bit flags
		ONLY_VERTICES,
		VERTICES_UV,
		VERTICES_UV_NORMALS
	};

	class MeshData
	{
	public:
		MeshData();
		MeshData(GLfloat* vertexData, GLsizei vetexArraySize, GLuint* indices, GLsizei indexArraySize, MeshAttributes attribs = MeshAttributes::ONLY_VERTICES);
		MeshData(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture*> textures);
		~MeshData();

		void drawElements() const;

		inline int getIndexCount() const { return _indexCount; }
		inline MeshAttributes getAttributeTypes() const { return _attribs; }

		std::vector<Texture*> textures;

		void disposeBuffers();

	private:

		std::vector<Vertex> _vertices;
		std::vector<GLuint> _indices;
		

		VertexArray* _vao;
		Buffer* _vbo;
		Buffer* _ebo;
		int _indexCount;
		MeshAttributes _attribs;
	};


}
}

#endif // !MESHDATA_H
