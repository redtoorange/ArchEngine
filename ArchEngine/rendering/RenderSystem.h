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

		void RenderModels(Camera* camera, ShaderProgram* shader) {
			if(shader) {
				shader->BindProgram();
				if(camera) {
					shader->SetUniformMat4("projection", camera->GetProjectionMatrix());
					shader->SetUniformMat4("view", camera->GetViewMatrix());
				}

				for(auto& modelSet : modelsToRender) {
					auto& model = modelSet.first;
					auto& instances = modelSet.second;

					for(auto& instace : instances) {
						instace->PrepareToRender(*shader);
						model->Render(*shader);
						instace->CleanUpFromRender();
					}
				}
			}

			modelsToRender.clear();
		}

		void AddModelInstance( ModelInstance* modelInstance) {
			modelsToRender[modelInstance->GetModel()].push_back(modelInstance);
		}

	private:
		std::map<Model*, std::vector<ModelInstance*>> modelsToRender;
		glm::vec4 m_clearColor{0.4f, 0.4f, 0.4f, 1};
	};
}
