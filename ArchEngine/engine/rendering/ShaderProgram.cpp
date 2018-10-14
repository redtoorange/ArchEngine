#include "ShaderProgram.h"
#include <sstream>
#include <fstream>
#include <SDL.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

namespace {
	const unsigned int MAX_LOG_LENGTH = 1024;

	std::string readFile(const std::string& path) {
		std::stringstream stream;

		std::ifstream fileStream{path};

		if (fileStream.good())
			stream << fileStream.rdbuf();
		else {
			std::stringstream errorstream;
			errorstream << "Failed to load shader at <" << path << ">.";
			SDL_Log(errorstream.str().c_str());
		}

		fileStream.close();

		return stream.str();
	}

	void LogShaderError(GLuint shader) {
		std::vector<GLchar> infoLog(MAX_LOG_LENGTH);
		GLsizei errorLength;
		glGetShaderInfoLog(shader, MAX_LOG_LENGTH, &errorLength, &infoLog[0]);

		std::stringstream stream;
		stream << "Failed to compile shader\n";
		for (int i = 0; i < errorLength; i++) {
			stream << infoLog[i];
		}

		SDL_Log(stream.str().c_str());
	}

	void LogProgramError(GLuint program) {
		std::vector<GLchar> infoLog(MAX_LOG_LENGTH);
		GLsizei errorLength;
		glGetProgramInfoLog(program, MAX_LOG_LENGTH, &errorLength, &infoLog[0]);

		std::stringstream stream;
		stream << "Failed to link program shader\n";
		for (int i = 0; i < errorLength; i++) {
			stream << infoLog[i];
		}

		SDL_Log(stream.str().c_str());
	}

	void CompileShader(GLuint shader, const std::string& source) {
		const GLchar* GLSource = (const GLchar *)source.c_str();
		glShaderSource(shader, 1, &GLSource, 0);
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			LogShaderError(shader);
		}
	}

	void LinkProgram(GLuint program, GLuint vertexShader, GLuint fragmentShader) {
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE) {
			LogProgramError(program);
		}
	}
}

namespace arch {
	ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
		const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		CompileShader(vertexShader, readFile(vertexPath));

		const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		CompileShader(fragmentShader, readFile(fragmentPath));

		m_programID = glCreateProgram();
		LinkProgram(m_programID, vertexShader, fragmentShader);

		// Cleanup
		glDetachShader(m_programID, vertexShader);
		glDetachShader(m_programID, fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void ShaderProgram::BindProgram() {
		glUseProgram(m_programID);
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(m_programID);
	}

	GLint ShaderProgram::GetUniformLocation(const std::string& name) const {
		return glGetUniformLocation(m_programID, name.c_str());
	}

	void ShaderProgram::SetUniformFloat(const std::string& name, const float& data) const {
		glUniform1f(GetUniformLocation(name), data);
	}

	void ShaderProgram::SetUniformMat4(const std::string& name, const glm::mat4& matrix) const {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ShaderProgram::SetUniformVec4(const std::string& name, const glm::vec4& vector) const {
		glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(vector));
	}

	void ShaderProgram::SetUniformVec3(const std::string& name, const glm::vec3& vector) const {
		glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vector));
	}
}
