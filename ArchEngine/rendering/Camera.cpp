#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace arch {

	Camera::Camera() {
		UpdateCamera();
	}

	glm::mat4 Camera::GetProjectionMatrix() const {
		return glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClipPlane, farClipPlane);
	}

	glm::mat4 Camera::GetViewMatrix() const {
		return glm::lookAt(position, position + Front, Up);
	}

	void Camera::UpdateCamera() {
		double pitch = rotation.x;
		double yaw = rotation.z;

		glm::vec3 front;
		front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
		front.y = glm::sin(glm::radians(pitch));
		front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

		Front = glm::normalize(front);

		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
}
