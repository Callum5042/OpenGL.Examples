#pragma once

#include "InputEvents.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GL
{
	class Camera : public Events::InputListener
	{
	public:
		Camera() = default;
		virtual ~Camera() = default;

		void Update();
		void Resize(int width, int height);

		constexpr glm::mat4 View() { return m_View; }
		constexpr glm::mat4 Projection() { return m_Projection; }

		// Mouse events
		void OnMouseDown(MouseData&& data) override;
		void OnMouseReleased(MouseData&& data) override;
		void OnMouseMotion(MouseData&& data) override;
		void OnMouseWheel(Events::MouseWheelEvent* e) override;

	private:
		glm::vec3 m_Position = glm::vec3(0, 0, -5);
		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Projection = glm::mat4(1.0f);

		float m_FOV = 85.0f;

		float m_Pitch = 30.0f;
		float m_Yaw = 90.0f;

		// Last mouse coordinates
		std::pair<int, int> m_LastMouseCoordinates;
	};
}