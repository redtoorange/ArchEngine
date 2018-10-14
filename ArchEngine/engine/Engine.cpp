#include "Engine.h"
#include <stdexcept>
#include "RenderSystem.h"
#include "InputSystem.h"
#include  "WindowSystem.h"
#include <iostream>
#include "AssetManager.h"

namespace arch {
	Engine* Engine::singleton = nullptr;

	Engine::Engine() {
		if (singleton)
			std::runtime_error("There can only be one instance of Engine.");
		singleton = this;

		SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		windowSystem = std::make_unique<WindowSystem>();
		SDL_GL_SetSwapInterval(0);

		if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
			std::exception("Failed to initialize OpenGL context");

		inputSystem = std::make_unique<InputSystem>();
		renderSystem = std::make_unique<RenderSystem>();
		assetManager = std::make_unique<AssetManager>();
	}

	Engine::~Engine() {
		// Stop all subsystems
		renderSystem.reset();
		inputSystem.reset();
		windowSystem.reset();
		assetManager.reset();

		singleton = nullptr;
		SDL_Quit();
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
				currentScreen->Render( *renderSystem );
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

	void Engine::Quit() {
		isRunning = false;
	}
}
