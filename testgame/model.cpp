#include "model.h"
namespace muongame {

Model::Model(GLfloat* vertices, GLsizei vetexArraySize,GLuint* indices, GLsizei indexArraySize) :
    _vao(new VertexArray()), _vbo(new Buffer()), _ebo(new Buffer(GL_ELEMENT_ARRAY_BUFFER)),
    _indexCount(indexArraySize/sizeof(GLuint))
{
    _vbo->load(vertices, vetexArraySize);
    _ebo->load(indices, indexArraySize);

    VertexArray::bind(_vao);
    _vao->addVertexAttributePointer(_vbo, 0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    Buffer::bind(_ebo);
    VertexArray::unbind();

}

Model::~Model()
{
    delete _vao;
    delete _vbo;
    delete _ebo;
}

void Model::draw()
{
    VertexArray::bind(_vao);
    glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
    VertexArray::unbind();
}

}