#pragma once

#include <memory>
#include "Window.h"

namespace arch {
	class WindowSystem {
	public:
		static WindowSystem* singleton;

		WindowSystem();

		virtual ~WindowSystem();

		void SwapBuffers();

		Window* GetCurrentWindow() const;

	private:
		std::unique_ptr<Window> m_currentWindow = nullptr;
	};
}
