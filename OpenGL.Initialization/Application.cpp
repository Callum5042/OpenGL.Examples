#include "Application.h"
#include <gl/glew.h>
#include <iostream>

bool Application::OnInitialise()
{
	if (!InitGlew())
		return false;

	return true;
}

void Application::OnRender()
{
	static const GLfloat blue[] = { 0.3f, 0.5f, 0.7f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, blue);


	SDL_GL_SetSwapInterval(0);
	SDL_GL_SwapWindow(GetWindow()->GetWindow());
}

void Application::OnQuit()
{
	Exit();
}

bool Application::InitGlew()
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