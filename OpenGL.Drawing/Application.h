#pragma once

#include <Engine.h>
#include "WindowEvents.h"
#include <gl/glew.h>
#include <string>

#include "Model.h"
#include "Camera.h"

namespace GL
{
	class Application : public Engine, public Events::WindowListener
	{
	public:
		Application() = default;

		bool OnInitialise() override;
		void OnUpdate() override;
		void OnRender() override;

		constexpr int ShaderId() { return m_ShaderId; }
		constexpr Camera* Camera() { return m_Camera; }

		// Window Events
		void OnQuit() override;
		void OnResize(int width, int height) override;

	private:
		bool InitGlew();

		Model* m_Model = nullptr;
		GL::Camera* m_Camera = nullptr;

		// Shaders
		GLuint m_ShaderId;
		GLuint m_VertexShader;
		GLuint m_FragmentShader;

		GLuint LoadVertexShader(std::string&& vertexPath);
		GLuint LoadFragmentShader(std::string&& fragmentPath);
		std::string ReadShader(std::string&& filename);
		bool HasCompiled(GLuint shader);
	};
}