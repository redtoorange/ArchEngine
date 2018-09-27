#pragma once
#include <SDL.h>

namespace arch {
	class Timer {
	public:
		Timer();
		float GetDeltaTime();
		void Update();

	private:
		float deltaTime;
		Uint64 last;
		Uint64 now;
	};
}

