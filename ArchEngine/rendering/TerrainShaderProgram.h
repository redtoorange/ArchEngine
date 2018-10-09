#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace arch {
	class TerrainShaderProgram : public ShaderProgram {
	public:
        TerrainShaderProgram();
		//ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);

        virtual ~TerrainShaderProgram();


        void SetGlobalIllumination(bool enable);

        void SetTerrainAlbedoColor(const glm::vec4& color);
		//virtual ~ShaderProgram();

		//void BindProgram();

		//GLint GetUniformLocation(const std::string& name) const;

		//void SetUniformMat4(const std::string& name, const glm::mat4& matrix) const;

		//void SetUniformVec4(const std::string& name, const glm::vec4& vector) const;

		//void SetUniformVec3(const std::string& name, const glm::vec3& vector) const;

	private:
        bool globalIllumination = false;
        glm::vec4 terrainAlbedo{0, 0, 0};
		//GLint m_programID;
	};

}
