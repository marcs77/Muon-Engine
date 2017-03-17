#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "../../util/fileutils.h"
#include "../../math/vec2.h"
#include "../../math/vec3.h"
#include "../../math/vec4.h"
#include "../../math/mat4.h"
#include <vector>
#include <map>
#include "../../util/log.h"
#include "../../util/color.h"

namespace muon {
	namespace graphics {
		class Shader {
		private:

			const char *_vertexPath, *_fragmentPath;
			GLuint load();
			GLuint loadShader(GLuint type, const char* path, bool &success);
			std::map<const GLchar*, GLint> _shaderUniforms;

		public:
			Shader(const char* vertexPath, const char* fragmentPath);
			~Shader();

            const GLuint shaderId;

			GLint getUniformLocation(const GLchar* name);

			void setUniform1f(const GLchar* name, float val);
			void setUniform1i(const GLchar* name, int val);
			void setUniform1iv(const GLchar * name, GLsizei count, const int* val);
			void setUniform2f(const GLchar* name, const math::Vec2f& val);
			void setUniform3f(const GLchar* name, const math::Vec3f& val);
			void setUniform4f(const GLchar* name, const math::Vec4f& val);
			void setUniformMat4(const GLchar* name, const math::Mat4& val);
			void setUniformColor(const GLchar* name, const Color& val);
		};

		class StandardShader : public Shader{
		public:
			StandardShader();

		};
	}
}

#endif // !SHADER_H
