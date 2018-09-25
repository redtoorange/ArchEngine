#pragma once
#include <vector>
#include <glad/glad.h>

namespace arch {
	class Mesh {
	public:
		Mesh(const std::vector<GLfloat>& vertices,
		     const std::vector<GLfloat>& colors,
		     const std::vector<GLfloat>& uvs,
		     const std::vector<GLfloat>& normals,
		     const std::vector<GLuint>& indices);

		~Mesh();

		void Render();

	private:
		std::vector<GLfloat> m_vertices;
		std::vector<GLfloat> m_colors;
		std::vector<GLfloat> m_uvs;
		std::vector<GLfloat> m_normals;
		std::vector<GLuint> m_indices;

		GLuint m_vbo;
		std::vector<GLuint> m_buffers;
	};
}
