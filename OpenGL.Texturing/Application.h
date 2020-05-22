#pragma once

#include <Engine.h>
#include "WindowEvents.h"
#include "InputEvents.h"

#include <string>

#include "Model.h"
#include "Camera.h"
#include "Shader.h"

namespace GL
{
	class Application : public Engine, public Events::WindowListener, public Events::InputListener
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		bool OnInitialise() override;
		void OnUpdate() override;
		void OnRender() override;

		constexpr std::unique_ptr<GL::Shader>& Shader() { return m_Shader; }
		constexpr std::unique_ptr<GL::Camera>& Camera() { return m_Camera; }

		// Window Events
		void OnQuit() override;
		void OnResize(int width, int height) override;

		// Inputs Events
		void OnKeyDown(Events::KeyData&& data) override;

	private:
		bool InitGlew();

		std::unique_ptr<GL::Model> m_Model = std::unique_ptr<GL::Model>(new GL::Model());
		std::unique_ptr<GL::Shader> m_Shader = std::unique_ptr<GL::Shader>(new GL::Shader());
		std::unique_ptr<GL::Camera> m_Camera = std::unique_ptr<GL::Camera>(new GL::Camera());

		bool m_Wireframe = false;
	};
}