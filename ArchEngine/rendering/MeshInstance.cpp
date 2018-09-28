#include "MeshInstance.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include "ShaderProgram.h"

namespace arch {

	MeshInstance::MeshInstance(Mesh* mesh) : m_sourceMesh(mesh) {}

	void MeshInstance::Translate(float x, float y, float z) {
		Translate({x, y, z});
	}

	void MeshInstance::Translate(const glm::vec3& amount) {
		m_position += amount;
	}

	void MeshInstance::Rotate(float pitch, float roll, float yaw) {
		Rotate({pitch, roll, yaw});
	}

	void MeshInstance::Rotate(const glm::vec3& amount) {
		m_rotation += amount;
	}

	void MeshInstance::Scale(float x, float y, float z) {
		Scale({x, y, x});
	}

	void MeshInstance::Scale(const glm::vec3& amount) {
		m_scale += amount;
	}

	void MeshInstance::SetPosition(float x, float y, float z) {
		SetPosition({x, y, z});
	}

	void MeshInstance::SetPosition(const glm::vec3& position) {
		m_position = position;
	}

	glm::vec3 MeshInstance::GetPosition() const {
		return m_position;
	}

	void MeshInstance::SetRotation(float pitch, float roll, float yaw) {
		SetRotation({pitch, roll, yaw});
	}

	void MeshInstance::SetRotation(const glm::vec3& rotation) {
		m_rotation = rotation;
	}

	glm::vec3 MeshInstance::GetRotation() const {
		return m_rotation;
	}

	void MeshInstance::SetScale(float x, float y, float z) {
		SetScale({x, y, z});
	}

	void MeshInstance::SetScale(const glm::vec3& scale) {
		m_scale = scale;
	}

	glm::vec3 MeshInstance::GetScale() const {
		return m_scale;
	}

	void MeshInstance::Render(ShaderProgram& shader) {
		shader.SetUniformMat4("transform", GetTransform());
		m_sourceMesh->Render();
	}

	glm::mat4 MeshInstance::GetTransform() const {
		glm::mat4 matrix(1);

		matrix = glm::translate(matrix, m_position);

		matrix = glm::rotate(matrix, glm::radians(m_rotation.x), {1, 0, 0});
		matrix = glm::rotate(matrix, glm::radians(m_rotation.y), {0, 1, 0});
		matrix = glm::rotate(matrix, glm::radians(m_rotation.z), {0, 0, 1});

		matrix = glm::scale(matrix, m_scale);

		return matrix;
	}
}
