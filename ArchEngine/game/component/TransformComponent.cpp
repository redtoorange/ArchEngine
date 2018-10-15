#include "TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>

namespace arch {
	void TransformComponent::Translate(float x, float y, float z) {
		Translate({x, y, z});
	}

	void TransformComponent::Translate(const glm::vec3& amount) {
		m_position += amount;
	}

	void TransformComponent::Rotate(float pitch, float roll, float yaw) {
		Rotate({pitch, roll, yaw});
	}

	void TransformComponent::Rotate(const glm::vec3& amount) {
		m_rotation += amount;
	}

	void TransformComponent::Scale(float x, float y, float z) {
		Scale({x, y, x});
	}

	void TransformComponent::Scale(const glm::vec3& amount) {
		m_scale += amount;
	}

	void TransformComponent::SetPosition(float x, float y, float z) {
		SetPosition({x, y, z});
	}

	void TransformComponent::SetPosition(const glm::vec3& position) {
		m_position = position;
	}

	glm::vec3 TransformComponent::GetPosition() const {
		return m_position;
	}

	void TransformComponent::SetRotation(float pitch, float roll, float yaw) {
		SetRotation({pitch, roll, yaw});
	}

	void TransformComponent::SetRotation(const glm::vec3& rotation) {
		m_rotation = rotation;
	}

	glm::vec3 TransformComponent::GetRotation() const {
		return m_rotation;
	}

	void TransformComponent::SetScale(float x, float y, float z) {
		SetScale({x, y, z});
	}

	void TransformComponent::SetScale(const glm::vec3& scale) {
		m_scale = scale;
	}

	glm::vec3 TransformComponent::GetScale() const {
		return m_scale;
	}

	glm::mat4 TransformComponent::GetTransformMatrix() const {
		glm::mat4 matrix(1);

		matrix = glm::translate(matrix, m_position);

		matrix = glm::rotate(matrix, glm::radians(m_rotation.x), {1, 0, 0});
		matrix = glm::rotate(matrix, glm::radians(m_rotation.y), {0, 1, 0});
		matrix = glm::rotate(matrix, glm::radians(m_rotation.z), {0, 0, 1});

		matrix = glm::scale(matrix, m_scale);

		return matrix;
	}
}
