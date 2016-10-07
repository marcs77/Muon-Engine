#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "../util/fileutils.h"
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/vec4.h"
#include "../math/mat4.h"
#include <vector>
#include <map>
#include "../util/log.h"

namespace muon {
	namespace graphics {
		class Shader {
		private:
			GLuint _shaderId;
			const char *_vertexPath, *_fragmentPath;
			GLuint load();
			GLuint loadShader(GLuint type, const char* path, bool &success);
			std::map<const GLchar*, GLint> _uniforms;

		public:
			Shader(const char* vertexPath, const char* fragmentPath);
			~Shader();

			inline GLuint getId() const { return _shaderId; };

			void use() const;
			void disable() const;

			GLint getUniformLocation(const GLchar* name);

			void setUniform1f(const GLchar* name, float val);
			void setUniform1i(const GLchar* name, int val);
			void setUniform1iv(const GLchar * name, GLsizei count, const int* val);
			void setUniform2f(const GLchar* name, math::Vec2f val);
			void setUniform3f(const GLchar* name, math::Vec3f val);
			void setUniform4f(const GLchar* name, math::Vec4f val);
			void setUniformMat4(const GLchar* name, math::Mat4 val);


		};
	}
}

#endif // !SHADER_H
