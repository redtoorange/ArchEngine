#include "GameScreen.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include <SDL.h>
#include <iostream>

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
		camera = std::make_unique<Camera>();
	}

	GameScreen::~GameScreen() {}

	void HandleKeys(Camera* camera, float deltaTime) {
		const Uint8* keys = SDL_GetKeyboardState(NULL);
		glm::vec3 inputDelta{ 0, 0, 0 };
		float speed = 10;

		// Forward back
		if (keys[SDL_SCANCODE_W])
			inputDelta.z += 1;
		if (keys[SDL_SCANCODE_S])
			inputDelta.z -= 1;
		
		// Left right
		if (keys[SDL_SCANCODE_A])
			inputDelta.x -= 1;
		if (keys[SDL_SCANCODE_D])
			inputDelta.x += 1;

		// Up down
		if (keys[SDL_SCANCODE_LCTRL])
			inputDelta.y -= 1;
		if (keys[SDL_SCANCODE_SPACE])
			inputDelta.y += 1;

		if (inputDelta.x != 0 || inputDelta.y != 0 || inputDelta.z != 0) {
			inputDelta = glm::normalize(inputDelta) * deltaTime * speed;
			camera->Translate(inputDelta);
		}
	}

	void GameScreen::Update(float deltaTime) {
		HandleKeys(camera.get(), deltaTime);


		instance->Rotate(0, 100 * deltaTime, 0);
		camera->UpdateCamera();
	}

	void GameScreen::Render() {

		shader->BindProgram();
		shader->SetUniformMat4("projection", camera->GetProjectionMatrix());
		shader->SetUniformMat4("view", camera->GetViewMatrix());

		instance->Render(*shader);
	}

	void GameScreen::Start() {
		shader->BindProgram();
	}

	void GameScreen::Paused() {}

	void GameScreen::Stop() {}
}
