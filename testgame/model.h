#ifndef MODEL_H
#define MODEL_H

#include "muon.h"

namespace muongame {

using namespace muon;
using namespace graphics;

enum ModelAttributes {
    ONLY_VERTICES,
    VERTICES_UV,
    VERTICES_UV_NORMALS
};

class Model
{
public:
    Model(GLfloat* vertexData, GLsizei vetexArraySize, GLuint* indices, GLsizei indexArraySize, ModelAttributes attribs = ModelAttributes::ONLY_VERTICES);
    ~Model();

    Color baseColor;

    void draw();

private:
    VertexArray* _vao;
    Buffer* _vbo;
    Buffer* _ebo;
    int _indexCount;
};

}

#endif // MODEL_H
