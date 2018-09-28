#include "Timer.h"

namespace arch {

	Timer::Timer() {
		now = SDL_GetPerformanceCounter();
		last = 0;
	}

	float Timer::GetDeltaTime() {
		return deltaTime;
	}

	void Timer::Update() {
		last = now;
		now = SDL_GetPerformanceCounter();
		deltaTime = static_cast<float>( (float)(now - last) * 1000 / (float)SDL_GetPerformanceFrequency()) * 0.001f;
	}
}
