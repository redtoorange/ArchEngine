#pragma once
#include <vector>
#include "Mesh.h"

#include <assimp/scene.h>

namespace arch {
	class Model {
	public:
		Model(const std::string& path);

		virtual ~Model();

		void Render(ShaderProgram& shader);

	private:
		std::string m_modelDirectory;
		std::vector<std::unique_ptr<Mesh>> m_modelMeshes;

		void LoadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	};
}
