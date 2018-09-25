#pragma once
#include "WindowSystem.h"
#include <vector>

namespace arch {
	class IInputListener;

	class InputSystem {
	public:
		static InputSystem* singleton;

		InputSystem();

		virtual ~InputSystem();

		void Update();

		void AddInputListener(IInputListener* listener);

		void RemoveInputListener(IInputListener* listener);

		void NotifyListeners();

	private:
		Window* currentWindow = nullptr;
		std::vector<IInputListener*> inputListeners;
	};
}
