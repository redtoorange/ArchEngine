#pragma once
#include <glm/glm.hpp>
#include "Model.h"


namespace arch {
	class ShaderProgram;

	class MeshInstance {
	public:
		MeshInstance(Mesh* mesh);

		void Translate(float x, float y, float z);

		void Translate(const glm::vec3& amount);

		void Rotate(float pitch, float roll, float yaw);

		void Rotate(const glm::vec3& amount);

		void Scale(float x, float y, float z);

		void Scale(const glm::vec3& amount);

		void SetPosition(float x, float y, float z);

		void SetPosition(const glm::vec3& position);

		glm::vec3 GetPosition() const;

		void SetRotation(float pitch, float roll, float yaw);

		void SetRotation(const glm::vec3& rotation);

		glm::vec3 GetRotation() const;

		void SetScale(float x, float y, float z);

		void SetScale(const glm::vec3& scale);

		glm::vec3 GetScale() const;

		glm::mat4 GetTransform() const;

		void Render(ShaderProgram& shader);

	private:
		glm::vec3 m_position{0, 0, 0};
		glm::vec3 m_rotation{0, 0, 0};
		glm::vec3 m_scale{1, 1, 1};

		Mesh* m_sourceMesh= nullptr;

	};
}
