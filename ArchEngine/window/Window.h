#pragma once

#include <string>
#include <SDL.h>

namespace arch {
	class Window {
	public:
		Window();

		Window(const std::string& windowTitle, int windowWidth, int windowHeight);

		virtual ~Window();

		void Init(const std::string& windowTitle, int windowWidth, int windowHeight);

		void SwapBuffers();

		void ClearWindow();

		SDL_Window* GetNativeHandle() const { return m_window; }

		bool ShouldClose() const;

		void SetShouldClose(bool shouldClose);

	private:
		SDL_Window* m_window = nullptr;
		SDL_GLContext m_context = nullptr;

		int m_windowWidth = 0;
		int m_windowHeight = 0;

		bool m_shouldClose = false;
	};

}
