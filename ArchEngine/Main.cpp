#ifdef _WIN32
#define APIENTRY __stdcall
#endif
#include <glad/glad.h>
#include <SDL.h>


#include "Model.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Engine.h"
#include "GameScreen.h"
using namespace std;

void Init() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	
	
}

int main(int argc, char* argv[]) {
	Init();

	arch::Engine engine;
	
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
		std::exception("Failed to initialize OpenGL context");

	SDL_GL_SetSwapInterval(1);
	
	std::unique_ptr<arch::GameScreen> gameScreen = std::make_unique<arch::GameScreen>();
	engine.SetScreen(gameScreen.get());

	engine.Run();

	SDL_Quit();

	return 0;
}
