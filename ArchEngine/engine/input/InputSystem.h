#pragma once
#include "WindowSystem.h"
#include <vector>

namespace arch {
	class IInputListener;

	struct MouseState {
		int x;
		int y;
		bool left;
		bool middle;
		bool right;
	};

	class InputSystem {
	public:
		static InputSystem* singleton;

		InputSystem();

		virtual ~InputSystem();

		void Update();

		void AddInputListener(IInputListener* listener);

		void RemoveInputListener(IInputListener* listener);

		void NotifyListeners();

		bool IsKeyPressed(int SDL_Scancode);

		MouseState GetRelativeMouseState() const;

	private:
		Window* currentWindow = nullptr;
		std::vector<IInputListener*> inputListeners;
		const Uint8* keyState = nullptr;
	};
}
