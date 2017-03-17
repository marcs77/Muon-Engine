#include "shader.h"
namespace muon {
	namespace graphics {

		Shader::Shader(const char * vertexPath, const char * fragmentPath) :
            _vertexPath(vertexPath), _fragmentPath(fragmentPath), shaderId(load())
		{

		}

		Shader::~Shader()
		{
            glDeleteProgram(shaderId);
		}

		GLint Shader::getUniformLocation(const GLchar * name)
		{
			if (_shaderUniforms.find(name) == _shaderUniforms.end()) {
				_shaderUniforms[name] = glGetUniformLocation(shaderId, name);
			}
			return _shaderUniforms[name];
		}

		void Shader::setUniform1f(const GLchar * name, float val)
		{
			glUniform1f(getUniformLocation(name), val);
		}

		void Shader::setUniform1i(const GLchar * name, int val)
		{
			glUniform1i(getUniformLocation(name), val);
		}

		void Shader::setUniform1iv(const GLchar * name, GLsizei count, const int* val)
		{
			glUniform1iv(getUniformLocation(name), count, val);
		}

		void Shader::setUniform2f(const GLchar * name, const math::Vec2f& val)
		{
			glUniform2f(getUniformLocation(name), val.x, val.y);
		}

		void Shader::setUniform3f(const GLchar * name, const math::Vec3f& val)
		{
            glUniform3f(getUniformLocation(name), (float)val.x, (float)val.y, (float)val.z);
		}

		void Shader::setUniform4f(const GLchar * name, const math::Vec4f& val)
		{
			glUniform4f(getUniformLocation(name), val.x, val.y, val.z, val.w);
		}

		void Shader::setUniformMat4(const GLchar * name, const math::Mat4& val)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, val.m);
		}

		void Shader::setUniformColor(const GLchar * name, const Color & val)
		{
			setUniform4f(name, val.getColor4f());
		}




		GLuint Shader::load()
		{
			GLuint program = glCreateProgram();
			bool success = false;
			GLuint vertex = loadShader(GL_VERTEX_SHADER, _vertexPath, success);
            if (!success) {
                ERR("Failed to compile vertex shader. ");
                glDeleteProgram(program);
                return 0;
            }
			GLuint fragment = loadShader(GL_FRAGMENT_SHADER, _fragmentPath, success);
            if (!success) {
                ERR("Failed to compile fragment shader. ");
                glDeleteProgram(program);
                return 0;
            }

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

            GLint result;

			glLinkProgram(program);
            glGetProgramiv(program, GL_LINK_STATUS, &result);

            if(result == GL_FALSE) {
                GLint msglen;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &msglen);
                std::vector<char> error(msglen);
                glGetProgramInfoLog(program, msglen, &msglen, &error[0]);
                ERR("OpenGL: /n" << &error[0]);
                glDeleteProgram(program);
                glDeleteShader(vertex);
                glDeleteShader(fragment);
                return 0;
            }

            glValidateProgram(program);
            glGetProgramiv(program, GL_VALIDATE_STATUS, &result);

            if(result == GL_FALSE) {
                GLint msglen;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &msglen);
                std::vector<char> error(msglen);
                glGetProgramInfoLog(program, msglen, &msglen, &error[0]);
                ERR("OpenGL: /n" << &error[0]);
                glDeleteProgram(program);
                glDeleteShader(vertex);
                glDeleteShader(fragment);
                return 0;
            }

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;

		}

		GLuint Shader::loadShader(GLuint type, const char * path, bool &success)
		{
			GLuint id = glCreateShader(type);
			std::string sr = read_file(path);
			if (sr.empty()) {
                ERR("Empty or missing shader file: " << path);
				glDeleteShader(id);
				success = false;
				return 0;
			}
			const char *src = sr.c_str();

			glShaderSource(id, 1, &src, NULL);
			glCompileShader(id);
			GLint result;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE) {
				GLint msglen;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &msglen);
				std::vector<char> error(msglen);
				glGetShaderInfoLog(id, msglen, &msglen, &error[0]);
				ERR("OpenGL: /n" << &error[0]);
				glDeleteShader(id);
				success = false;
				return 0;
			}

			success = true;
			return id;
		}

	}
}

