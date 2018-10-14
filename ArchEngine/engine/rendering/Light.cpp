#include "Light.h"
#include "ShaderProgram.h"

namespace arch {
	glm::vec3 Light::GetPosition() const { return m_position; }

	void Light::SetPosition(const glm::vec3& position) { m_position = position; }

	glm::vec4 Light::GetColor() const { return m_color; }

	void Light::SetColor(const glm::vec4& color) { m_color = color; }

	void Light::Render(const ShaderProgram& shader) const {
		shader.SetUniformVec3("lightposition", m_position);
		shader.SetUniformVec4("lightColor", m_color);
	}
}

