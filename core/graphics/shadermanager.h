#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "shader.h"
namespace muon {
namespace graphics {

class ShaderManager
{
private:
    static Shader* _currentShader;

public:

    static inline Shader* getCurrentShader() { return _currentShader; }

    static void useShader(Shader* shader);
    static void disableShader();
};


}
}
#endif // SHADERMANAGER_H
