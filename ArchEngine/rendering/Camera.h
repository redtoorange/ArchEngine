#pragma once
#include <glm/glm.hpp>

namespace arch {
	class Camera {
	public:
		Camera() = default;

		virtual ~Camera() = default;

		virtual glm::mat4 GetProjectionMatrix() const = 0;

		virtual glm::mat4 GetViewMatrix() const = 0;

		virtual void UpdateCamera() = 0;

		virtual void Translate(float x, float y, float z) = 0;

		virtual void Translate(const glm::vec3& amount) = 0;

		virtual void Rotate(float x, float y, float z) = 0;

		virtual void Rotate(const glm::vec3& amount) = 0;
	};
}
