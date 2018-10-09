#include "Mesh.h"
#include "ShaderProgram.h"
#include <SDL.h>

namespace {
	template <typename T>
	GLuint BindToVBO(const std::vector<T>& data, GLuint attribute, GLuint length, GLenum dataType) {
		GLuint vbo;

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(attribute);
		glVertexAttribPointer(attribute, length, dataType, GL_FALSE, 0, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return vbo;
	}
}

namespace arch {
	Mesh::Mesh(const std::vector<GLfloat>& vertices,
	           const std::vector<GLfloat>& colors,
	           const std::vector<GLfloat>& uvs,
	           const std::vector<GLfloat>& normals,
	           const std::vector<GLuint>& indices,
	           const std::vector<Texture>& textures)
		:
		m_indexCount(static_cast<GLuint>(indices.size())), m_textures(textures) {

		// Create and Bind VAO
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		m_buffers.push_back(BindToVBO(vertices, 0, 3, GL_FLOAT));

		if (!colors.empty())
			m_buffers.push_back(BindToVBO(colors, 1, 4, GL_FLOAT));

		if (!uvs.empty())
			m_buffers.push_back(BindToVBO(uvs, 2, 2, GL_FLOAT));

		if (!normals.empty())
			m_buffers.push_back(BindToVBO(normals, 3, 3, GL_FLOAT));

		// Bind indices
		GLuint ebo;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(),
		             GL_STATIC_DRAW);
		m_buffers.push_back(ebo);

		glBindVertexArray(0);
	}

	Mesh::~Mesh() {
		Destroy();
	}

	void Mesh::Destroy() {
		SDL_Log("Mesh Destroyed");
		for (const auto& buffer : m_buffers) {
			glDeleteBuffers(1, &buffer);
		}

		glDeleteVertexArrays(1, &m_vao);
	}

	void Mesh::Render(ShaderProgram& shader) {
		 unsigned int diffuseNum = 1;
		 unsigned int specularNum = 1;
		 for (unsigned int i = 0; i < m_textures.size(); i++) {
		 	glActiveTexture(GL_TEXTURE0 + i);
  
		 	std::string number;
		 	std::string name = m_textures[i].type;
  
		 	if(name == "texture_diffuse") 
		 		number = std::to_string(diffuseNum++);
		 	else if(name == "texture_specular")
		 		number = std::to_string(specularNum++);
  
		 	shader.SetUniformFloat(("material" + name + number).c_str(), i);
		 	glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
		 		
		 }
		 glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
