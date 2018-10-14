#pragma once
// #include "Texture.h"
// #include "ShaderProgram.h"
#include <map>
#include <memory>
#include "Texture.h"

/**
 * The AssetManager is responsible for the loading and unloading of all game resources.  The manage maintains a cache 
 * of all loaded resources.  When a resource is no longer referenced, it will be unload from memory and automatically
 * cleaned up.
 */
namespace arch {
	class Model;

	class AssetManager {
	public:
		static AssetManager* singleton;

		AssetManager();

		virtual ~AssetManager();

		Texture LoadTexture(const std::string& texturePath, const std::string& typeName);

		Model* LoadModel(const std::string& modelPath);

	private:
		std::map<std::string, std::unique_ptr<Model>> m_modelCache;
		std::map<std::string, Texture> m_textureCache;

	};
}
