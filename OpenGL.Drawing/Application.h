#pragma once

#include <Engine.h>
#include "WindowEvents.h"

#include <string>

#include "Model.h"
#include "Camera.h"
#include "Shader.h"

namespace GL
{
	class Application : public Engine, public Events::WindowListener
	{
	public:
		Application() = default;

		bool OnInitialise() override;
		void OnUpdate() override;
		void OnRender() override;

		constexpr Shader* Shader() { return m_Shader; }
		constexpr Camera* Camera() { return m_Camera; }

		// Window Events
		void OnQuit() override;
		void OnResize(int width, int height) override;

	private:
		bool InitGlew();

		Model* m_Model = nullptr;
		GL::Shader* m_Shader = nullptr;
		GL::Camera* m_Camera = nullptr;
	};
}