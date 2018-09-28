#include "Engine.h"
#include <stdexcept>
#include "RenderSystem.h"
#include "InputSystem.h"
#include  "WindowSystem.h"
#include <iostream>

namespace arch {
	Engine* Engine::singleton = nullptr;

	Engine::Engine() {
		if (singleton)
			std::runtime_error("There can only be one instance of Engine.");

		singleton = this;

		// Start all subsystems
		windowSystem = std::make_unique<WindowSystem>();
		inputSystem = std::make_unique<InputSystem>();
		renderSystem = std::make_unique<RenderSystem>();
	}

	Engine::~Engine() {
		// Stop all subsystems
		renderSystem.reset();
		inputSystem.reset();
		windowSystem.reset();

		singleton = nullptr;
	}

	void Engine::Run() {
		isRunning = true;

		int frames = 0;
		float elapsed = 0;

		while (isRunning) {
			timer.Update();

			inputSystem->Update();

			renderSystem->ClearScreen();
			if (currentScreen) {
				currentScreen->Update(timer.GetDeltaTime());
				currentScreen->Render();
			}
			windowSystem->SwapBuffers();

			elapsed += timer.GetDeltaTime();
			frames++;
			if(elapsed >= 1) {
				elapsed -= 1;
				std::cout << frames << "\n";
				frames = 0;
			}
			
		}
	}

	void Engine::SetScreen(IScreen* newScreen) {
		if (currentScreen == newScreen)
			return;

		if (currentScreen)
			currentScreen->Stop();

		currentScreen = newScreen;

		if (currentScreen)
			currentScreen->Start();
	}
}
