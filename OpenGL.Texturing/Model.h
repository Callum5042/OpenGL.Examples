#pragma once

#include <gl/glew.h>
#include <string>

#include <glm/gtc/matrix_transform.hpp>

namespace GL
{
	class Model
	{
	public:
		Model() = default;
		virtual ~Model();

		void Load();
		void Render();

		void LoadTexture(std::string&& texture_path);

	private:
		GLuint m_VertexArrayObject;
		GLuint m_VertexBuffer;
		GLuint m_IndexBuffer;

		GLuint m_DiffuseTextureId;


		glm::mat4 tex_overlay_transform = glm::mat4(1.0f);
	};
}