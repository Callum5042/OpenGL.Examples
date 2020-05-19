#pragma once

#include <Engine.h>
#include "WindowEvents.h"
#include <gl/glew.h>
#include <string>

class Application : public Engine, public Events::WindowListener
{
public:
	Application() = default;

	bool OnInitialise() override;
	void OnRender() override;

	// Window Events
	void OnQuit() override;
	void OnResize(int width, int height) override;

private:
	bool InitGlew();

	// Shaders
	GLuint m_ShaderId;
	GLuint m_VertexShader;
	GLuint m_FragmentShader;

	GLuint LoadVertexShader(std::string&& vertexPath);
	GLuint LoadFragmentShader(std::string&& fragmentPath);
	std::string ReadShader(std::string&& filename);
	bool HasCompiled(GLuint shader);

	// Drawing code
	GLuint m_VertexArrayObject;
	GLuint m_VertexBuffer;
	GLuint m_IndexBuffer;
};