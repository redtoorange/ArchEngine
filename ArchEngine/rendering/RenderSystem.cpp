#include "RenderSystem.h"
#include <stdexcept>
#include <glad/glad.h>

namespace arch {
	RenderSystem* RenderSystem::singleton = nullptr;

	RenderSystem::RenderSystem() {
		if (singleton)
			std::runtime_error("There can only be one instance of RenderSystem.");

		singleton = this;
	}

	RenderSystem::~RenderSystem() {
		singleton = nullptr;
	}

	void RenderSystem::ClearScreen() {
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
