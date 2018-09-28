#pragma once
#include "IScreen.h"
#include <memory>
#include "MeshInstance.h"

namespace arch {
	class Mesh;
	class ShaderProgram;

	class GameScreen : public IScreen {
	public:
		GameScreen();

		virtual ~GameScreen();

		void Update(float deltaTime) override;

		void Render() override;

		void Start() override;

		void Paused() override;

		void Stop() override;

	private:
		std::unique_ptr<MeshInstance> instance;
		std::unique_ptr<Mesh> mesh;
		std::unique_ptr<ShaderProgram> shader;
	};

}
