#pragma once
#include <map>
#include <glm/glm.hpp>
#include "ModelInstance.h"
#include <vector>
#include "Camera.h"

#include "ShaderProgram.h"
#include "Camera.h"
#include "ModelInstance.h"
#include "Model.h"

namespace arch {
	class RenderSystem {
	public:
		static RenderSystem* singleton;

		RenderSystem();

		virtual ~RenderSystem();

		void ClearScreen();

		void BeginBatch(Camera* camera, ShaderProgram* shader);

		void AddModelInstance(ModelInstance* modelInstance);

		void EndBatch();

	private:
		std::map<Model*, std::vector<ModelInstance*>> modelsToRender;
		glm::vec4 m_clearColor{0.4f, 0.4f, 0.4f, 1};

		bool batching = false;
		Camera* m_currentCamera = nullptr;
		ShaderProgram* m_currentShader = nullptr;
	};
}
