#pragma once
#include <glm/glm.hpp>

namespace arch {
	class Camera {
	public:
		Camera();

		glm::mat4 GetProjectionMatrix() const;

		glm::mat4 GetViewMatrix() const;

		void UpdateCamera();

		void Translate(float x, float y, float z);
		void Translate(const glm::vec3& amount);

		void Rotate(float x, float y, float z);
		void Rotate(const glm::vec3& amount);

	private:
		glm::vec3 position{0, 0, 5};
		glm::vec3 rotation{0, 0, -90.0f};

		glm::vec3 Front{0, 0, -1.0f};
		glm::vec3 Up{0, 1.0f, 0};
		glm::vec3 WorldUp{0, 1.0f, 0};
		glm::vec3 Right{1.0f, 0, 0};

		float aspectRatio = 1440.0f / 900.0f;
		float fieldOfView = 90.0f;
		float nearClipPlane = 0.1f;
		float farClipPlane = 100.0f;
	};
}
