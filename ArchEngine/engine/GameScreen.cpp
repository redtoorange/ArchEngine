#include "GameScreen.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include <SDL.h>
#include <iostream>
#include "InputSystem.h"
#include "ModelInstance.h"
#include "PerspectiveCamera.h"
#include "RenderSystem.h"

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
		const std::vector<Texture> textures = {};
	}

	GameScreen::GameScreen() {
		mesh = std::make_unique<Mesh>(positions, colors, uvs, normals, indices, textures);
		shader = std::make_unique<ShaderProgram>(
			"C:\\workspace\\cpp\\projects\\ArchEngine\\shaders\\basic.vert", 
			"C:\\workspace\\cpp\\projects\\ArchEngine\\shaders\\basic.frag");
		instance = std::make_unique<MeshInstance>(mesh.get());
		camera = std::make_unique<PerspectiveCamera>();
		SDL_SetRelativeMouseMode(SDL_TRUE);

		nanoSuit = std::make_unique<Model>("C:\\workspace\\cpp\\projects\\ArchEngine\\assets\\nano\\nanosuit.obj");
		// nanoSuit = std::make_unique<Model>("C:\\workspace\\cpp\\projects\\ArchEngine\\assets\\kenney\\station.obj");
		nanoSuitInst1 = std::make_unique<ModelInstance>(nanoSuit.get());
		nanoSuitInst1->Translate(10, 0, -5);
		nanoSuitInst1->SetScale(0.5f, 0.5f, 0.5f);
		
		nanoSuitInst2 = std::make_unique<ModelInstance>(nanoSuit.get());
		nanoSuitInst2->Translate(5, 0, -5);
		nanoSuitInst2->SetScale(0.5f, 0.5f, 0.5f);

		nanoSuitInst3 = std::make_unique<ModelInstance>(nanoSuit.get());
		nanoSuitInst3->Translate(0, 0, -5);
		nanoSuitInst3->SetScale(0.5f, 0.5f, 0.5f);

		nanoSuitInst4 = std::make_unique<ModelInstance>(nanoSuit.get());
		nanoSuitInst4->Translate(-5, 0, -5);
		nanoSuitInst4->SetScale(0.5f, 0.5f, 0.5f);

		light = std::make_unique<Light>(glm::vec3{0, 10, 0}, glm::vec4{1, 1, 1, 1});
	}

	GameScreen::~GameScreen() {}

	void GameScreen::HandleKeys(float deltaTime) {
		auto input = InputSystem::singleton;

		glm::vec3 inputDelta{ 0, 0, 0 };
		float speed = 10;

		// Forward back
		if (input->IsKeyPressed(SDL_SCANCODE_W))
			inputDelta.z += 1;
		if (input->IsKeyPressed(SDL_SCANCODE_S))
			inputDelta.z -= 1;
		
		// Left right
		if (input->IsKeyPressed(SDL_SCANCODE_A))
			inputDelta.x -= 1;
		if (input->IsKeyPressed(SDL_SCANCODE_D))
			inputDelta.x += 1;

		// Change Color of Light
		if (input->IsKeyPressed(SDL_SCANCODE_R))
			light->SetColor({1, 0, 0, 1});
		if (input->IsKeyPressed(SDL_SCANCODE_G))
			light->SetColor({ 0, 1, 0, 1 });
		if (input->IsKeyPressed(SDL_SCANCODE_B))
			light->SetColor({ 0, 0, 1, 1 });
		if (input->IsKeyPressed(SDL_SCANCODE_T))
			light->SetColor({ 1, 1, 1, 1 });
;

		// Up down
		if (input->IsKeyPressed(SDL_SCANCODE_SPACE))
			inputDelta.y += 1;
		if (input->IsKeyPressed(SDL_SCANCODE_LCTRL))
			inputDelta.y -= 1;

		if (inputDelta.x != 0 || inputDelta.y != 0 || inputDelta.z != 0) {
			inputDelta = glm::normalize(inputDelta) * deltaTime * speed;
			camera->Translate(inputDelta);
		}
	}

	void GameScreen::HandleMouse() {
		MouseState state = InputSystem::singleton->GetRelativeMouseState();
		float mouseSensitivity = 0.05f;
		
		camera->Rotate(-state.y * mouseSensitivity, 0, state.x * mouseSensitivity);

		if (state.middle) {
			SDL_Log("Middle mouse pressed");
		}
		if (state.right) {
			SDL_Log("Right mouse pressed");
		}

	}

	void GameScreen::Update(float deltaTime) {
		HandleKeys(deltaTime);
		HandleMouse();

		// instance->Rotate(0, 100 * deltaTime, 0);
		camera->UpdateCamera();
	}

	void GameScreen::Render( RenderSystem& renderer ) {
		light->Render(*shader);

		renderer.AddModelInstance(nanoSuitInst1.get());
		renderer.AddModelInstance(nanoSuitInst2.get());
		renderer.AddModelInstance(nanoSuitInst3.get());
		renderer.AddModelInstance(nanoSuitInst4.get());

		renderer.RenderModels(camera.get(), shader.get());
	}

	void GameScreen::Start() {
		shader->BindProgram();
	}

	void GameScreen::Paused() {}

	void GameScreen::Stop() {}
}
