#pragma once
#include <glad/glad.h>
#include <string>

namespace arch {
	struct Texture {
		GLuint id;
		std::string type;
		std::string path;
	};
}
