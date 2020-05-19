#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

void GL::Shader::Load(std::string&& vertexPath, std::string&& fragmentPath)
{
	m_ShaderId = glCreateProgram();
	GLuint m_VertexShader = LoadVertexShader(std::move(vertexPath));
	GLuint m_FragmentShader = LoadFragmentShader(std::move(fragmentPath));

	// Link
	glAttachShader(m_ShaderId, m_VertexShader);
	glAttachShader(m_ShaderId, m_FragmentShader);

	glLinkProgram(m_ShaderId);
}

void GL::Shader::Use()
{
	glUseProgram(m_ShaderId);
}

GLuint GL::Shader::LoadVertexShader(std::string&& vertexPath)
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

GLuint GL::Shader::LoadFragmentShader(std::string&& fragmentPath)
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

bool GL::Shader::HasCompiled(GLuint shader)
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

std::string GL::Shader::ReadShader(std::string&& filename)
{
	std::ifstream file(filename);

	std::stringstream source;
	source << file.rdbuf();

	return source.str();
}
