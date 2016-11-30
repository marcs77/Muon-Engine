#ifndef MODEL_H
#define MODEL_H

#include "muon.h"

namespace muongame {

using namespace muon;
using namespace graphics;

class Model
{
public:
    Model(GLfloat* vertices, GLsizei vetexArraySize, GLuint* indices, GLsizei indexArraySize);
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
