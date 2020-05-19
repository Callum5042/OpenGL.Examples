#include "Application.h"
#include <gl/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool GL::Application::OnInitialise()
{
	if (!InitGlew())
		return false;

	m_Shader = new GL::Shader();
	m_Shader->Load("D:\\Sources\\Testing\\OpenGL.Testing\\OpenGL.Drawing\\VertexShader.glsl", "D:\\Sources\\Testing\\OpenGL.Testing\\OpenGL.Drawing\\FragmentShader.glsl");

	m_Model = new GL::Model();
	m_Model->Load();

	m_Camera = new GL::Camera();

	return true;
}

void GL::Application::OnUpdate()
{
	m_Camera->Update();
}

void GL::Application::OnRender()
{
	static const GLfloat blue[] = { 0.3f, 0.5f, 0.7f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, blue);

	m_Shader->Use();
	m_Model->Render();

	SDL_GL_SetSwapInterval(0);
	SDL_GL_SwapWindow(GetWindow()->GetWindow());
}

void GL::Application::OnQuit()
{
	Exit();
}

void GL::Application::OnResize(int width, int height)
{
	m_Camera->Resize(width, height);
	glViewport(0, 0, width, height);
}

bool GL::Application::InitGlew()
{
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << "Error: " << glewGetErrorString(error) << '\n';
		return false;
	}

#ifdef _DEBUG
	const unsigned char* glewVersion = glewGetString(GLEW_VERSION);
	std::cout << "Glew Version: " << glewVersion << '\n';
#endif

	return true;
}