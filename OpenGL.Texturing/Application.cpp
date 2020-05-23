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

	m_Shader->Load("D:\\Sources\\Testing\\OpenGL.Testing\\OpenGL.Texturing\\VertexShader.glsl", "D:\\Sources\\Testing\\OpenGL.Testing\\OpenGL.Texturing\\FragmentShader.glsl");

	m_Model->Load();
	m_Model->LoadTexture("C:/Users/Callum/Pictures/wall.jpg");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	 
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

	static GLfloat depth = 1.0f;
	glClearBufferfv(GL_DEPTH, 0, &depth);

	m_Shader->Use();

	if (m_Wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

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

void GL::Application::OnKeyDown(Events::KeyData&& data)
{
	if (data.key == SDL_SCANCODE_1)
	{
		m_Wireframe = !m_Wireframe;
	}
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