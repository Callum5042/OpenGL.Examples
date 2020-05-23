#include "Model.h"
#include "Application.h"
#include <SDL_messagebox.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Vertex
{
	Vertex(float x, float y, float z, float u, float v) : x(x), y(y), z(z), u(u), v(v) {}

	float x;
	float y;
	float z;

	float u;
	float v;
};

GL::Model::~Model()
{
	glDeleteTextures(1, &m_DiffuseTextureId);

	glDeleteVertexArrays(1, &m_VertexArrayObject);
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_IndexBuffer);
}

void GL::Model::Load()
{
	Vertex vertices[] =
	{
		{ -1.0f, -1.0f, -1.0f, 0.0f, 1.0f },
		{ -1.0f, +1.0f, -1.0f, 0.0f, 0.0f },
		{ +1.0f, +1.0f, -1.0f, 1.0f, 0.0f },
		{ +1.0f, -1.0f, -1.0f, 1.0f, 1.0f },

		{ -1.0f, -1.0f, +1.0f, 1.0f, 1.0f },
		{ +1.0f, -1.0f, +1.0f, 0.0f, 1.0f },
		{ +1.0f, +1.0f, +1.0f, 0.0f, 0.0f },
		{ -1.0f, +1.0f, +1.0f, 1.0f, 0.0f },

		{ -1.0f, +1.0f, -1.0f, 0.0f, 1.0f },
		{ -1.0f, +1.0f, +1.0f, 0.0f, 0.0f },
		{ +1.0f, +1.0f, +1.0f, 1.0f, 0.0f },
		{ +1.0f, +1.0f, -1.0f, 1.0f, 1.0f },

		{ -1.0f, -1.0f, -1.0f, 1.0f, 1.0f },
		{ +1.0f, -1.0f, -1.0f, 0.0f, 1.0f },
		{ +1.0f, -1.0f, +1.0f, 0.0f, 0.0f },
		{ -1.0f, -1.0f, +1.0f, 1.0f, 0.0f },

		{ -1.0f, -1.0f, +1.0f, 0.0f, 1.0f },
		{ -1.0f, +1.0f, +1.0f, 0.0f, 0.0f },
		{ -1.0f, +1.0f, -1.0f, 1.0f, 0.0f },
		{ -1.0f, -1.0f, -1.0f, 1.0f, 1.0f },

		{ +1.0f, -1.0f, -1.0f, 0.0f, 1.0f },
		{ +1.0f, +1.0f, -1.0f, 0.0f, 0.0f },
		{ +1.0f, +1.0f, +1.0f, 1.0f, 0.0f },
		{ +1.0f, -1.0f, +1.0f, 1.0f, 1.0f }
	};

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23,
	};

	// Vertex Array Object
	glCreateVertexArrays(1, &m_VertexArrayObject);
	glBindVertexArray(m_VertexArrayObject);

	// Vertex Buffer
	glCreateBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

	glNamedBufferStorage(m_VertexBuffer, sizeof(vertices), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(m_VertexBuffer, 0, sizeof(vertices), vertices);

	// Index Buffer
	glCreateBuffers(1, &m_IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Something pipeline
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
}

void GL::Model::Render()
{
	Application* app = reinterpret_cast<Application*>(Engine::Get());

	// Update shader transform
	glm::mat4 transform = glm::mat4(1.0f);
	unsigned int transformLoc = glGetUniformLocation(app->Shader()->ShaderId(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	// Update shader view
	unsigned int viewLoc = glGetUniformLocation(app->Shader()->ShaderId(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(app->Camera()->View()));

	// Update shader projection
	unsigned int projLoc = glGetUniformLocation(app->Shader()->ShaderId(), "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(app->Camera()->Projection()));

	// Draw
	glBindVertexArray(m_VertexArrayObject);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

void GL::Model::LoadTexture(std::string&& texture_path)
{
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texture_path.c_str(), &width, &height, &nrChannels, 0);
	if (data == nullptr)
	{
		std::string err("Failed to load texture: ");
		err.append(stbi_failure_reason());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", err.c_str(), nullptr);
	}

	// Create texture
	glCreateTextures(GL_TEXTURE_2D, 1, &m_DiffuseTextureId);
	glTextureStorage2D(m_DiffuseTextureId, 2, GL_RGB8, width, height);
	glTextureSubImage2D(m_DiffuseTextureId, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	glBindTextureUnit(0, m_DiffuseTextureId);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
}