#pragma once
#include "IScreen.h"
#include <memory>
#include "Timer.h"

namespace arch {
	class WindowSystem;
	class InputSystem;
	class RenderSystem;
	class AssetManager;

	class Engine {
	public:
		static Engine* singleton;

		Engine();

		virtual ~Engine();

		void Run();

		void SetScreen(IScreen* newScreen);

		void Quit();

	private:
		bool isRunning = false;

		IScreen* currentScreen = nullptr;
		std::unique_ptr<WindowSystem> windowSystem = nullptr;
		std::unique_ptr<InputSystem> inputSystem = nullptr;
		std::unique_ptr<RenderSystem> renderSystem = nullptr;
		std::unique_ptr<AssetManager> assetManager = nullptr;

		Timer timer;
	};

}
