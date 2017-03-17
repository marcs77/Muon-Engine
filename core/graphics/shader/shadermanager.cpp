#include "shadermanager.h"

namespace muon {
namespace graphics {

    Shader* ShaderManager::_currentShader;
	math::Mat4 ShaderManager::_modelMatrix(1.0);
	math::Mat4 ShaderManager::_viewMatrix(1.0);
	math::Mat4 ShaderManager::_projMatrix(1.0);

    void ShaderManager::useShader(const Shader *shader) {
        if(_currentShader != shader) {
            _currentShader = (Shader*) shader;
            glUseProgram(_currentShader->shaderId);
			setModelMatrix(_modelMatrix);
			setViewMatrix(_viewMatrix);
			setProjectionMatrix(_projMatrix);
        }
    }

    void ShaderManager::disableShader() {
        _currentShader = NULL;
        glUseProgram(0);
    }

	void ShaderManager::setProjectionMatrix(const math::Mat4 & matrix)
	{
		setUniformMatrix("pr_matrix", matrix);
		_projMatrix = matrix;
	}

	void ShaderManager::setViewMatrix(const math::Mat4 & matrix)
	{
		setUniformMatrix("vw_matrix", matrix);
		_viewMatrix = matrix;
	}

	void ShaderManager::setModelMatrix(const math::Mat4 & matrix)
	{
		setUniformMatrix("ml_matrix", matrix);
		_modelMatrix = matrix;
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
