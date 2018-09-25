#pragma once
#include <string>
#include <glad/glad.h>

namespace arch {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);

		void BindProgram();

	private:
		GLint m_programID;
	};

}
