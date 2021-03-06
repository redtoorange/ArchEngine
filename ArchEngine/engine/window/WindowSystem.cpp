﻿#include "WindowSystem.h"

namespace arch {
	WindowSystem* WindowSystem::singleton = nullptr;

	WindowSystem::WindowSystem() {
		if (singleton)
			std::runtime_error("There can only be one instance of WindowSystem.");

		singleton = this;
		m_currentWindow = std::make_unique<Window>("Arch Engine", 1440, 900);
	}

	WindowSystem::~WindowSystem() {
		singleton = nullptr;
	}

	void WindowSystem::SwapBuffers() {
		if (m_currentWindow) {
			m_currentWindow->SwapBuffers();
		}
	}

	Window* WindowSystem::GetCurrentWindow() const {
		return m_currentWindow.get();
	}
}
