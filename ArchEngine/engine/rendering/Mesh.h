#pragma once
#include <vector>
#include <glad/glad.h>
#include "Texture.h"

namespace arch {
	class ShaderProgram;

	class Mesh {
	public:
		Mesh(const std::vector<GLfloat>& vertices,
		     const std::vector<GLfloat>& colors,
		     const std::vector<GLfloat>& uvs,
		     const std::vector<GLfloat>& normals,
		     const std::vector<GLuint>& indices,
			 const std::vector<Texture>& textures);

		~Mesh();

		void PrepareToRender(ShaderProgram& shader);

		void Render(ShaderProgram& shader);

		void CleanUpFromRender();

		void Destroy();

	private:
		GLuint m_vao;
		GLuint m_indexCount;

		std::vector<Texture> m_textures;
		std::vector<GLuint> m_buffers;
	};
}
