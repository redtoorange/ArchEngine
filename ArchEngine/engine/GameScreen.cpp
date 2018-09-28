#include "GameScreen.h"
#include "Mesh.h"
#include "ShaderProgram.h"

namespace arch {
	namespace {
		const std::vector<GLfloat> positions = {
				-0.5f, 0.5f, 0.0f, // TOP_LEFT
				-0.5f, -0.5f, 0.0f, // BOT_LEFT
				0.5f, -0.5f, 0.0f, // BOT_RIGHT
				0.5f, 0.5f, 0.0f // TOP_RIGHT
		};
		const std::vector<GLfloat> colors = {
				1.0f, 0.0f, 0.0f, 1.0f,
				0.0f, 1.0f, 0.0f, 1.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				1.0f, 0.0f, 1.0f, 1.0f 
		};
		const std::vector<GLfloat> normals = {};
		const std::vector<GLfloat> uvs = {};
		const std::vector<GLuint> indices = {
				0, 2, 1,
				0, 3, 2 
		};
	}

	GameScreen::GameScreen() {
		mesh = std::make_unique<Mesh>(positions, colors, uvs, normals, indices);
		shader = std::make_unique<ShaderProgram>(
			"C:\\workspace\\cpp\\projects\\ArchEngine\\shaders\\basic.vert", 
			"C:\\workspace\\cpp\\projects\\ArchEngine\\shaders\\basic.frag");
		instance = std::make_unique<MeshInstance>(mesh.get());
	}

	GameScreen::~GameScreen() {}

	void GameScreen::Update(float deltaTime) {
		instance->Rotate(0, 100 * deltaTime, 0);
	}

	void GameScreen::Render() {
		instance->Render(*shader);
	}

	void GameScreen::Start() {
		shader->BindProgram();
	}

	void GameScreen::Paused() {}

	void GameScreen::Stop() {}
}
