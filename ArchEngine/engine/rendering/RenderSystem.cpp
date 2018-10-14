#include "RenderSystem.h"
#include <stdexcept>
#include <glad/glad.h>

namespace arch {
	RenderSystem* RenderSystem::singleton = nullptr;

	void RenderSystem::BeginBatch(Camera* camera, ShaderProgram* shader) {
		if (!batching) {
			m_currentCamera = camera;
			m_currentShader = shader;
			batching = true;
		}
		else {
			std::runtime_error("A batch is currently open, call EndBatch() before openning a new batch.");
		}

	}

	void RenderSystem::AddModelInstance(ModelInstance* modelInstance) {
		if (batching) {
			modelsToRender[modelInstance->GetModel()].push_back(modelInstance);
		}
		else {
			std::runtime_error("Cannot add a model to a batch before BeginBatch()");
		}

	}

	void RenderSystem::EndBatch() {
		if (batching) {
			if (m_currentShader) {
				m_currentShader->BindProgram();
				if (m_currentCamera) {
					m_currentShader->SetUniformMat4("projection", m_currentCamera->GetProjectionMatrix());
					m_currentShader->SetUniformMat4("view", m_currentCamera->GetViewMatrix());
				}

				for (auto& modelSet : modelsToRender) {
					auto& model = modelSet.first;
					auto& instances = modelSet.second;

					for (auto& instace : instances) {
						instace->PrepareToRender(*m_currentShader);
						model->Render(*m_currentShader);
						instace->CleanUpFromRender();
					}
				}
			}

			modelsToRender.clear();
			batching = false;
		}
		else {
			std::runtime_error("Cannot call EndBatch() before BeginBatch().");
		}

	}

	RenderSystem::RenderSystem() {
		if (singleton)
			std::runtime_error("There can only be one instance of RenderSystem.");

		singleton = this;

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	RenderSystem::~RenderSystem() {
		singleton = nullptr;
	}

	void RenderSystem::ClearScreen() {
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
