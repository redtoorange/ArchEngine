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
		//deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );
		deltaTime = static_cast<double>( (double)(now - last) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001f;
	}
}
