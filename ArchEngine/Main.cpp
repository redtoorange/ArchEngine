#include <SDL.h>
#include <glad/glad.h>
#include "Engine.h"
#include "GameScreen.h"

int main(int argc, char* argv[]) {
	arch::Engine engine;
	
	std::unique_ptr<arch::GameScreen> gameScreen = std::make_unique<arch::GameScreen>();
	engine.SetScreen(gameScreen.get());
	engine.Run();

	return 0;
}
