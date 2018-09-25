#include "ModelInstance.h"

namespace arch {

	void ModelInstance::Translate(float x, float y, float z) {
		Translate({x, y, z});
	}

	void ModelInstance::Translate(const glm::vec3& amount) {
		m_position += amount;
	}

	void ModelInstance::Rotate(float pitch, float roll, float yaw) {
		Rotate({pitch, roll, yaw});
	}

	void ModelInstance::Rotate(const glm::vec3& amount) {
		m_rotation += amount;
	}

	void ModelInstance::Scale(float x, float y, float z) {
		Scale({x, y, x});
	}

	void ModelInstance::Scale(const glm::vec3& amount) {
		m_scale += amount;
	}

	void ModelInstance::SetPosition(float x, float y, float z) {
		SetPosition({x, y, z});
	}

	void ModelInstance::SetPosition(const glm::vec3& position) {
		m_position = position;
	}

	glm::vec3 ModelInstance::GetPosition() const {
		return m_position;
	}

	void ModelInstance::SetRotation(float pitch, float roll, float yaw) {
		SetRotation({pitch, roll, yaw});
	}

	void ModelInstance::SetRotation(const glm::vec3& rotation) {
		m_rotation = rotation;
	}

	glm::vec3 ModelInstance::GetRotation() const {
		return m_rotation;
	}

	void ModelInstance::SetScale(float x, float y, float z) {
		SetScale({x, y, z});
	}

	void ModelInstance::SetScale(const glm::vec3& scale) {
		m_scale = scale;
	}

	glm::vec3 ModelInstance::GetScale() const {
		return m_scale;
	}

	void ModelInstance::Render() {
		if(m_sourceModel) {

			m_sourceModel->Render();
		}
	}
}
