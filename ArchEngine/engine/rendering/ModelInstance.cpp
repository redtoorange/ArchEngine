#include "ModelInstance.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include "ShaderProgram.h"
#include "Model.h"

namespace arch {
	ModelInstance::ModelInstance(Model* model) : m_sourceModel(model) {}

	void ModelInstance::Translate(float x, float y, float z) {
		Translate({ x, y, z });
	}

	void ModelInstance::Translate(const glm::vec3& amount) {
		m_position += amount;
	}

	void ModelInstance::Rotate(float pitch, float roll, float yaw) {
		Rotate({ pitch, roll, yaw });
	}

	void ModelInstance::Rotate(const glm::vec3& amount) {
		m_rotation += amount;
	}

	void ModelInstance::Scale(float x, float y, float z) {
		Scale({ x, y, x });
	}

	void ModelInstance::Scale(const glm::vec3& amount) {
		m_scale += amount;
	}

	void ModelInstance::SetPosition(float x, float y, float z) {
		SetPosition({ x, y, z });
	}

	void ModelInstance::SetPosition(const glm::vec3& position) {
		m_position = position;
	}

	glm::vec3 ModelInstance::GetPosition() const {
		return m_position;
	}

	void ModelInstance::SetRotation(float pitch, float roll, float yaw) {
		SetRotation({ pitch, roll, yaw });
	}

	void ModelInstance::SetRotation(const glm::vec3& rotation) {
		m_rotation = rotation;
	}

	glm::vec3 ModelInstance::GetRotation() const {
		return m_rotation;
	}

	void ModelInstance::SetScale(float x, float y, float z) {
		SetScale({ x, y, z });
	}

	void ModelInstance::SetScale(const glm::vec3& scale) {
		m_scale = scale;
	}

	glm::vec3 ModelInstance::GetScale() const {
		return m_scale;
	}

	/**
	 * @shader Shader to upload this instance's transform to.  This shader will be passed down the the 
	 * source model.
	 */
	void ModelInstance::PrepareToRender(ShaderProgram& shader) {
		shader.SetUniformMat4("transform", GetTransform());
	}

	void ModelInstance::CleanUpFromRender() {
		// Stub
	}

	/**
	 * @return The source model of this ModelInstance.
	 */
	Model* ModelInstance::GetModel() const {
		return m_sourceModel;
	}

	glm::mat4 ModelInstance::GetTransform() const {
		glm::mat4 matrix(1);

		matrix = glm::translate(matrix, m_position);

		matrix = glm::rotate(matrix, glm::radians(m_rotation.x), { 1, 0, 0 });
		matrix = glm::rotate(matrix, glm::radians(m_rotation.y), { 0, 1, 0 });
		matrix = glm::rotate(matrix, glm::radians(m_rotation.z), { 0, 0, 1 });

		matrix = glm::scale(matrix, m_scale);

		return matrix;
	}
}