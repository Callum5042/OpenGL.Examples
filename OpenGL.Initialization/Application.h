#pragma once

#include <Engine.h>
#include "WindowEvents.h"

namespace GL
{
	class Application : public Engine, public Events::WindowListener
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		bool OnInitialise() override;
		void OnRender() override;

		// Window Events
		void OnQuit() override;

	private:
		bool InitGlew();
	};
}