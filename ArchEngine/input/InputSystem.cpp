#include "InputSystem.h"
#include "IInputListener.h"
#include "InputEvent.h"
#include <iostream>
#include "Engine.h"

namespace arch {
	InputSystem* InputSystem::singleton = nullptr;

	InputSystem::InputSystem() {
		if (singleton)
			std::runtime_error("There can only be one instance of InputSystem.");

		singleton = this;

		currentWindow = WindowSystem::singleton->GetCurrentWindow();
	}
	
	InputSystem::~InputSystem() {
		singleton = nullptr;
	}

	void InputSystem::Update() {
		if(currentWindow) {
			SDL_Event event;
			while(SDL_PollEvent(&event)) {

				// Handle Window Events
				if(event.type == SDL_WINDOWEVENT) {
					switch(event.window.event) {
					case SDL_WINDOWEVENT_CLOSE:
						SDL_Log("Window Closed.");
						Engine::singleton->Quit();
						break;
					case SDL_WINDOWEVENT_MOVED:
						SDL_Log("Window Moved.");
						break;
					}
				}

				else if(event.type == SDL_KEYDOWN) {
					
				}
				else if (event.type == SDL_KEYUP) {
					switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						SDL_Log("Window Closed.");
						Engine::singleton->Quit();
						break;
					}
				}

			}
		}
	}

	void InputSystem::AddInputListener(IInputListener* listener) {
		if (listener) {
			inputListeners.push_back(listener);
		}
	}

	void InputSystem::RemoveInputListener(IInputListener* listener) {
		if (listener) {
			for (auto iter = inputListeners.begin(); iter != inputListeners.end(); ++iter) {
				if (*iter == listener) {
					inputListeners.erase(iter);
					return;
				}
			}
		}
	}

	void InputSystem::NotifyListeners() {
		// Create the InputEvent
		InputEvent event;

		for (const auto& listener : inputListeners) {
			bool handled = listener->Notify(event);
			if (handled)
				break;
		}
	}
}
