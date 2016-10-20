#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "shader.h"
#include "math/mat4.h"
#include "util/log.h"

namespace muon {
namespace graphics {

class ShaderManager
{
private:
    static Shader* _currentShader;
	static math::Mat4 _projMatrix;
	static math::Mat4 _viewMatrix;

	static void setUniformMatrix(const GLchar* name, const math::Mat4& matrix);

public:

    static inline Shader* getCurrentShader() { return _currentShader; }

    static void useShader(Shader* shader);
    static void disableShader();

	static void setProjectionMatrix(const math::Mat4& matrix);
	static void setViewMatrix(const math::Mat4& matrix);
	static void setModelMatrix(const math::Mat4& matrix);

};


}
}
#endif // SHADERMANAGER_H
