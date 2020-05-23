#include "Camera.h"
#include <SDL_mouse.h>
#include "Application.h"

void GL::Camera::Update()
{
	float distance = 5.0f;

	glm::vec3 direction;
	direction.x = distance * cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	direction.y = distance * sin(glm::radians(m_Pitch));
	direction.z = distance * sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

	m_Position = direction;

	glm::vec3 eye = m_Position = direction;
	glm::vec3 at(0, 0, 0);
	glm::vec3 up(0, 1, 0);

	m_View = glm::lookAt(eye, at, up);
}

void GL::Camera::Resize(int width, int height)
{
	m_Projection = glm::perspective(glm::radians(m_FOV), ((float)width / height), 0.1f, 100.0f);
}

void GL::Camera::OnMouseDown(MouseData&& data)
{
	if (data.button == MouseButton::MOUSE_LMASK)
	{
		m_LastMouseCoordinates.first = data.x;
		m_LastMouseCoordinates.second = data.y;
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
}

void GL::Camera::OnMouseReleased(MouseData&& data)
{
	if (data.button == MouseButton::MOUSE_LMASK)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_WarpMouseGlobal(m_LastMouseCoordinates.first, m_LastMouseCoordinates.second);
	}
}

void GL::Camera::OnMouseMotion(MouseData&& data)
{
	if (data.button == MouseButton::MOUSE_LMASK)
	{
		m_Yaw += (data.xrel * 0.25f);
		m_Pitch += (data.yrel * 0.25f);

		m_Pitch = std::clamp<float>(m_Pitch, -89, 89);
	}
}

void GL::Camera::OnMouseWheel(Events::MouseWheelEvent* e)
{
	m_FOV -= static_cast<int>(e->wheel);
	m_FOV = std::clamp<float>(m_FOV, 1.0f, 180.0f);

	auto& window = Application::Get()->GetWindow();
	Resize(window->GetWidth(), window->GetHeight());
}