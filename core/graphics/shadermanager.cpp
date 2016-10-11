#include "shadermanager.h"

namespace muon {
namespace graphics {

    Shader* ShaderManager::_currentShader;

    void ShaderManager::useShader(Shader *shader) {
        _currentShader = shader;
        glUseProgram(_currentShader->shaderId);
    }

    void ShaderManager::disableShader() {
        glUseProgram(0);
    }

}
}
