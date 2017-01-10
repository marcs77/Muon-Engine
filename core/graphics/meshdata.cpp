#include "meshdata.h"
#include "../util/log.h"
namespace muon {
namespace graphics {

	MeshData::MeshData(GLfloat* vertexData, GLsizei vetexArraySize, GLuint* indices, GLsizei indexArraySize, MeshAttributes attribs) :
		_vao(new VertexArray()), _vbo(new Buffer()), _ebo(new Buffer(GL_ELEMENT_ARRAY_BUFFER)),
		_indexCount(indexArraySize / sizeof(GLuint))
	{
		_vbo->load(vertexData, vetexArraySize);
		_ebo->load(indices, indexArraySize);

		VertexArray::bind(_vao);
		switch (attribs)
		{
		case VERTICES_UV_NORMALS:
			_vao->addVertexAttributePointer(_vbo, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
			_vao->addVertexAttributePointer(_vbo, 1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			_vao->addVertexAttributePointer(_vbo, 2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
			break;
		case VERTICES_UV:
			_vao->addVertexAttributePointer(_vbo, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			_vao->addVertexAttributePointer(_vbo, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			break;
		default:
			ERR("Invalid enum for MeshAttributes, using ONLY_VERTICES.");
		case ONLY_VERTICES:
			_vao->addVertexAttributePointer(_vbo, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			break;
		
		}
		Buffer::bind(_ebo);
		VertexArray::unbind();
	}

	MeshData::~MeshData()
	{
		delete _vao;
		delete _vbo;
		delete _ebo;
	}

	void MeshData::drawElements()
	{
		VertexArray::bind(_vao);
		glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
		VertexArray::unbind();
	}

}
}