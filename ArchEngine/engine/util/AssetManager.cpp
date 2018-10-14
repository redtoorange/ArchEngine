#include "AssetManager.h"
#include "Model.h"
#include "RenderSystem.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>
#include <SDL.h>

namespace {
	arch::Texture LoadFromFile(const std::string& path, const std::string& typeName) {
		arch::Texture texture;
		texture.path = path;
		texture.type = typeName;

		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nChannels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nChannels, 0);
		if(data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else {
			SDL_Log("Failed to load texture.");
		}
		stbi_image_free(data);

		texture.id = textureID;
		return texture;
	}
}

namespace arch {
	AssetManager* AssetManager::singleton = nullptr;

	AssetManager::AssetManager() {
		if (singleton)
			std::runtime_error("There can only be one instance of RenderSystem.");

		singleton = this;
	}

	AssetManager::~AssetManager() {
		// TODO Cleanup assets

		singleton = nullptr;
	}

	Model* AssetManager::LoadModel(const std::string& modelPath) {
		const auto iter = m_modelCache.find(modelPath);

		if (iter != m_modelCache.end())
			return iter->second.get();

		// Model* model = ModelLoader::LoadModel(modelPath);
		// m_modelCache[modelPath].reset(1model);
		// return model;

		return nullptr;
	}

	Texture AssetManager::LoadTexture(const std::string& texturePath, const std::string& typeName) {
		const auto iter = m_textureCache.find(texturePath);

		if (iter != m_textureCache.end())
			return iter->second;

		Texture texture = LoadFromFile(texturePath, typeName);
		m_textureCache[texturePath] = texture;
		return texture;
	}
}
