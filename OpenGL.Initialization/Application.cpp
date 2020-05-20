#include "Application.h"
#include <gl/glew.h>
#include <iostream>

bool GL::Application::OnInitialise()
{
	if (!InitGlew())
		return false;

	std::cout << "OpenGL: " << glGetString(GL_VERSION) << '\n';
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << '\n';
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n';
	std::cout << "Shader: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';

	return true;
}

void GL::Application::OnRender()
{
	static const GLfloat blue[] = { 0.3f, 0.5f, 0.7f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, blue);


	SDL_GL_SetSwapInterval(0);
	SDL_GL_SwapWindow(GetWindow()->GetWindow());
}

void GL::Application::OnQuit()
{
	Exit();
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
	std::cout << "Glew: " << glewVersion << '\n';
#endif

	return true;
}