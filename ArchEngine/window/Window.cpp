#include "Window.h"
#include <glad/glad.h>

namespace arch {
	Window::Window() {}

	Window::Window(const std::string& windowTitle, int windowWidth, int windowHeight) {
		Init(windowTitle, windowWidth, windowHeight);
	}

	Window::~Window() {
		if (m_window) {
			SDL_GL_DeleteContext(m_context);
			SDL_DestroyWindow(m_window);
			m_context = nullptr;
			m_window = nullptr;
		}
	}

	void Window::Init(const std::string& windowTitle, int windowWidth, int windowHeight) {
		m_windowWidth = windowWidth;
		m_windowHeight = windowHeight;

		m_window = SDL_CreateWindow(windowTitle.c_str(),
		                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		                            windowWidth, windowHeight,
		                            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (!m_window)
			std::exception("Failed to create window.");

		m_context = SDL_GL_CreateContext(m_window);
		if (!m_context)
			std::exception("Failed to create context.");

		SDL_GL_MakeCurrent(m_window, m_context);
	}

	void Window::SwapBuffers() {
		SDL_GL_SwapWindow(m_window);
	}

	void Window::ClearWindow() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::SetShouldClose(bool shouldClose) { m_shouldClose = shouldClose; }

	bool Window::ShouldClose() const {
		return m_shouldClose;
	}

}
