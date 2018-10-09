﻿#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>

namespace arch {

	Camera::Camera() {
		UpdateCamera();
	}

	void Camera::Translate(float x, float y, float z) {
		Translate({x, y, z});
	}

	void Camera::Translate(const glm::vec3& amount) {
		glm::vec3 delta{0, 0, 0};

		delta += Front * amount.z;
		delta += Right * amount.x;
		delta += Up * amount.y;

		position += delta;
	}

	void Camera::Rotate(float x, float y, float z) {
		Rotate({x, y, z});
	}

	void Camera::Rotate(const glm::vec3& amount) {
		rotation += amount;
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
		front.x = static_cast<float>(glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)));
		front.y = static_cast<float>(glm::sin(glm::radians(pitch)));
		front.z = static_cast<float>(glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch)));

		Front = glm::normalize(front);

		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
}
