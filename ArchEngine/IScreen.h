#pragma once

namespace arch {
	class IScreen {
	public:
		virtual void Update(float deltaTime) = 0;

		virtual void Render() = 0;

		virtual void Start() = 0;

		virtual void Paused() = 0;

		virtual void Stop() = 0;

	};

}
