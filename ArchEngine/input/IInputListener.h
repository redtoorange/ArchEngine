#pragma once

namespace arch {
	class InputEvent;

	class IInputListener {
	public:
		IInputListener() = default;
		virtual ~IInputListener() = default;
		virtual bool Notify(const InputEvent& event) = 0;
	};
}
