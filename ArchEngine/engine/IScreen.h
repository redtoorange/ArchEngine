#pragma once

namespace arch {
	class RenderSystem;

	class IScreen {
	public:
		virtual ~IScreen() = default;

		virtual void Update(float deltaTime) = 0;

		virtual void Render(RenderSystem& renderer) = 0;

		virtual void Start() = 0;

		virtual void Paused() = 0;

		virtual void Stop() = 0;

	};

}
