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

	m_Model = new GL::Model();
	m_Model->Load();

	m_Camera = new GL::Camera();

	// Shaders
	m_ShaderId = glCreateProgram();
	GLuint m_VertexShader = LoadVertexShader("D:\\Sources\\Testing\\OpenGL.Testing\\OpenGL.Drawing\\VertexShader.glsl");
	GLuint m_FragmentShader = LoadFragmentShader("D:\\Sources\\Testing\\OpenGL.Testing\\OpenGL.Drawing\\FragmentShader.glsl");

	// Link
	glAttachShader(m_ShaderId, m_VertexShader);
	glAttachShader(m_ShaderId, m_FragmentShader);

	glLinkProgram(m_ShaderId);
	glUseProgram(m_ShaderId);

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

GLuint GL::Application::LoadVertexShader(std::string&& vertexPath)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	std::string vertexShaderSource = ReadShader(std::move(vertexPath));
	const GLchar* vertexC = vertexShaderSource.c_str();

	glShaderSource(vertexShader, 1, &vertexC, NULL);
	glCompileShader(vertexShader);

	if (!HasCompiled(vertexShader))
	{
		return false;
	}

	return vertexShader;
}

GLuint GL::Application::LoadFragmentShader(std::string&& fragmentPath)
{
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string fragmentShaderSource = ReadShader(std::move(fragmentPath));
	const GLchar* fragmentC = fragmentShaderSource.c_str();

	glShaderSource(fragmentShader, 1, &fragmentC, NULL);
	glCompileShader(fragmentShader);

	if (!HasCompiled(fragmentShader))
	{
		return false;
	}

	return fragmentShader;
}

bool GL::Application::HasCompiled(GLuint shader)
{
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
#ifdef _DEBUG
		GLsizei len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

#pragma warning(suppress: 26451)
		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(shader, len, &len, log);
		std::cerr << "Shader compilation failed: " << log << std::endl;
		delete[] log;
#endif /* DEBUG */

		return false;
	}

	return true;
}

std::string GL::Application::ReadShader(std::string&& filename)
{
	std::ifstream file(filename);

	std::stringstream source;
	source << file.rdbuf();

	return source.str();
}
