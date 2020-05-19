#include "Model.h"
#include "Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void GL::Model::Load()
{
	static const GLfloat vertices[] =
	{
		-0.5, +0.5, 0.0f,
		+0.5, +0.5, 0.0f,
		+0.5, -0.5, 0.0f,
		-0.5, -0.5, 0.0f
	};

	static const GLushort indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	static const GLfloat colours[] =
	{
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(vertices));
	glEnableVertexAttribArray(1);
}

void GL::Model::Render()
{
	Application* app = reinterpret_cast<Application*>(Engine::Get());

	// Update shader transform
	glm::mat4 transform = glm::mat4(1.0f);
	unsigned int transformLoc = glGetUniformLocation(app->ShaderId(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	// Update shader view

	unsigned int viewLoc = glGetUniformLocation(app->ShaderId(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(app->Camera()->View()));

	// Update shader projection
	unsigned int projLoc = glGetUniformLocation(app->ShaderId(), "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(app->Camera()->Projection()));

	// Draw
	glBindVertexArray(m_VertexArrayObject);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}