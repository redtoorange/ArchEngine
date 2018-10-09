#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SDL.h>
#include "AssetManager.h"

namespace arch {
	Model::Model(const std::string& path) {
		LoadModel(path);
	}

	Model::~Model() {
		for (unsigned int i = 0; i < m_modelMeshes.size(); i++)
			m_modelMeshes[i]->Destroy();
	}

	void Model::Render(ShaderProgram& shader) {
		for (unsigned int i = 0; i < m_modelMeshes.size(); i++) {
			m_modelMeshes[i]->Render(shader);
		}
	}

	void Model::LoadModel(const std::string& path) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_FixInfacingNormals);

		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			const std::string error = "ERROR LOADING <";
			SDL_Log((error + path + ">").c_str());
			return;
		}

		m_modelDirectory = path.substr(0, path.find_last_of('\\'));
		processNode(scene->mRootNode, scene);
	}

	void Model::processNode(aiNode* node, const aiScene* scene) {
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			processMesh(mesh, scene);
			
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++) {
			processNode(node->mChildren[i], scene);
		}
	}

	void Model::processMesh(aiMesh* mesh, const aiScene* scene) {
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> colors;
		std::vector<GLfloat> uvs;
		std::vector<GLfloat> normals;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			// Process verts
			vertices.push_back(mesh->mVertices[i].x);
			vertices.push_back(mesh->mVertices[i].y);
			vertices.push_back(mesh->mVertices[i].z);

			// Process colors
			if(mesh->HasVertexColors(i)) {
				colors.push_back(mesh->mColors[i]->r);
				colors.push_back(mesh->mColors[i]->g);
				colors.push_back(mesh->mColors[i]->b);
				colors.push_back(mesh->mColors[i]->a);
			}

			// Process UVs
			if(mesh->mTextureCoords[0]) {
				uvs.push_back(mesh->mTextureCoords[0][i].x);
				uvs.push_back(mesh->mTextureCoords[0][i].y);
			}
			else {
				uvs.push_back(0.0f);
				uvs.push_back(0.0f);
			}

			// Process normals
			normals.push_back(mesh->mNormals[i].x);
			normals.push_back(mesh->mNormals[i].y);
			normals.push_back(mesh->mNormals[i].z);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		 if(mesh->mMaterialIndex >= 0) {
		 	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
  
		 	std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		 	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
  
		 	std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		 	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		 }

		m_modelMeshes.emplace_back( new Mesh(vertices, colors, uvs, normals, indices, textures));
		// return Mesh(vertices, colors, uvs, normals, indices, textures);
	}

	std::vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName) {
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
			aiString str;
			material->GetTexture(type, i, &str);
			textures.push_back(AssetManager::singleton->LoadTexture(m_modelDirectory + "\\" + str.C_Str(), typeName));
		}

		return textures;
	}
}
