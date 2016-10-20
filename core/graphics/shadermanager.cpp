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

	void ShaderManager::setProjectionMatrix(const math::Mat4 & matrix)
	{
		setUniformMatrix("pr_matrix", matrix);
	}

	void ShaderManager::setViewMatrix(const math::Mat4 & matrix)
	{
		setUniformMatrix("vw_matrix", matrix);
	}

	void ShaderManager::setModelMatrix(const math::Mat4 & matrix)
	{
		setUniformMatrix("ml_matrix", matrix);
	}

	void ShaderManager::setUniformMatrix(const GLchar * name, const math::Mat4& matrix)
	{
		if (_currentShader) {
			_currentShader->setUniformMat4(name, matrix);
		}
		else {
			ERR("Can't load uniform: no active shader.")
		}
	}
}
}
