#include "shadermanager.h"

namespace muon {
namespace graphics {

    Shader* ShaderManager::_currentShader;

    void ShaderManager::useShader(Shader *shader) {
        if(_currentShader != shader) {
            _currentShader = shader;
            glUseProgram(_currentShader->shaderId);
        }
    }

    void ShaderManager::disableShader() {
        _currentShader = NULL;
        glUseProgram(0);
    }

}
}
