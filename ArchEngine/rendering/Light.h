#pragma once
#include <glm/glm.hpp>

namespace arch {
	class ShaderProgram;

	class Light {
	public:

		Light(const glm::vec3& position, const glm::vec4& color)
			: m_position(position),
			m_color(color) {}

		glm::vec3 GetPosition() const;

		void SetPosition(const glm::vec3& position);

		glm::vec4 GetColor() const;

		void SetColor(const glm::vec4& color);

		void Render(const ShaderProgram& shader) const;

	private:
		glm::vec3 m_position{ 0, 0, 0 };
		glm::vec4 m_color{ 0, 0, 0, 1 };
	};

}

