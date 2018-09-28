#pragma once
#include <glm/glm.hpp>

namespace arch {
	class Camera {
	public:
		Camera();

		glm::mat4 GetProjectionMatrix() const;

		glm::mat4 GetViewMatrix() const;

		void UpdateCamera();

	private:
		glm::vec3 position{0, 0, 5};
		glm::vec3 rotation{0, 0, -90.0f};

		glm::vec3 Front{0, 0, -1.0f};
		glm::vec3 Up{0, 1.0f, 0};
		glm::vec3 WorldUp{0, 1.0f, 0};
		glm::vec3 Right{1.0f, 0, 0};

		float aspectRatio = 800.0f / 600.0f;
		float fieldOfView = 90.0f;
		float nearClipPlane = 0.1f;
		float farClipPlane = 100.0f;
	};
}
