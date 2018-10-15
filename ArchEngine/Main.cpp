#include <SDL.h>
#include <glad/glad.h>
#include "Engine.h"
#include "GameScreen.h"

int main(int argc, char* argv[]) {
	// Start the Engine!
	arch::Engine engine;

	// Load up a test screen
	arch::GameScreen gameScreen;
	engine.SetScreen(&gameScreen);

	// Start main loop
	engine.Run();

	return 0;
}
