﻿#include "RenderSystem.h"
#include <stdexcept>
#include <glad/glad.h>

namespace arch {
	RenderSystem* RenderSystem::singleton = nullptr;

	RenderSystem::RenderSystem() {
		if (singleton)
			std::runtime_error("");

		singleton = this;
	}

	RenderSystem::~RenderSystem() {
		singleton = nullptr;
	}

	void RenderSystem::Render() {
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render some stuff
	}
}