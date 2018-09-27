#pragma once
#include "IScreen.h"
#include <memory>
#include "Timer.h"

namespace arch {
	class WindowSystem;
	class InputSystem;
	class RenderSystem;

	class Engine {
	public:
		static Engine* singleton;

		Engine();

		virtual ~Engine();

		void Run();

		void SetScreen(IScreen* newScreen);

	private:
		bool isRunning = false;

		IScreen* currentScreen = nullptr;
		std::unique_ptr<WindowSystem> windowSystem = nullptr;
		std::unique_ptr<InputSystem> inputSystem = nullptr;
		std::unique_ptr<RenderSystem> renderSystem = nullptr;

		Timer timer;
	};

}
