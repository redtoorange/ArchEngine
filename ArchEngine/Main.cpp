#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>
#include <SDL.h>

#include <iostream>
#include <WindowSystem.h>
#include <InputSystem.h>
#include <RenderSystem.h>
#include "IInputListener.h"
#include "Model.h"
#include "Mesh.h"
#include "ShaderProgram.h"
using namespace std;

std::unique_ptr<arch::WindowSystem> windowSystem;
std::unique_ptr<arch::InputSystem> inputSystem;
std::unique_ptr<arch::RenderSystem> renderSystem;

// class KeyboardListener : public arch::IInputListener {
// public:
// 	bool Notify(const arch::InputEvent& event) override {
// 		
// 	}
// };

void Init() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	windowSystem = std::make_unique<arch::WindowSystem>();
	inputSystem = std::make_unique<arch::InputSystem>();
	renderSystem = std::make_unique<arch::RenderSystem>();

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		std::exception("Failed to initialize OpenGL context");
	}
}

int main(int argc, char* argv[]) {
	Init();

	arch::Mesh mesh(
		{
			-0.5f, 0.5f, 0.0f, // TOP_LEFT
			-0.5f, -0.5f, 0.0f, // BOT_LEFT
			0.5f, -0.5f, 0.0f, // BOT_RIGHT
			0.5f, 0.5f, 0.0f // TOP_RIGHT
		},
		{
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 1.0f
		},
		{},
		{},
		{
			0, 2, 1,
			0, 3, 2
		});

	arch::ShaderProgram shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");

	while (!windowSystem->ShouldClose()) {
		inputSystem->Update();

		renderSystem->Render();

		shader.BindProgram();
		mesh.Render();

		windowSystem->SwapBuffers();
	}

	renderSystem.reset();
	inputSystem.reset();
	windowSystem.reset();

	SDL_Quit();

	return 0;
}
