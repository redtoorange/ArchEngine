#include "Mesh.h"

namespace arch {
	Mesh::Mesh(const std::vector<GLfloat>& vertices,
	           const std::vector<GLfloat>& colors,
	           const std::vector<GLfloat>& uvs,
	           const std::vector<GLfloat>& normals,
	           const std::vector<GLuint>& indices)
		:
		m_vertices(vertices),
		m_colors(colors),
		m_uvs(uvs),
		m_normals(normals),
		m_indices(indices) {

		// Create and Bind VAO
		glGenVertexArrays(1, &m_vbo);
		glBindVertexArray(m_vbo);

		// Bind vertices
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		m_buffers.push_back(vbo);

		// Bind colors
		GLuint cbo;
		glGenBuffers(1, &cbo);
		glBindBuffer(GL_ARRAY_BUFFER, cbo);
		glBufferData(GL_ARRAY_BUFFER, m_colors.size() * sizeof(GLfloat), m_colors.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(1); 
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		m_buffers.push_back(cbo);

		// Bind indices
		GLuint ebo;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(),
		             GL_STATIC_DRAW);
		m_buffers.push_back(ebo);


		glBindVertexArray(0);
	}

	Mesh::~Mesh() {
		for(const auto& buffer : m_buffers) {
			glDeleteBuffers(1, &buffer);
		}

		glDeleteVertexArrays(1, &m_vbo);
	}

	void Mesh::Render() {
		glBindVertexArray(m_vbo);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
