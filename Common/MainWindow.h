#pragma once

#include <SDL_video.h>
#include <string>

class MainWindow
{
public:
	MainWindow();
	MainWindow(MainWindow&) = delete;
	MainWindow& operator=(MainWindow&) = delete;
	virtual ~MainWindow();

	bool Create(std::string&& title, int width, int height);
	void Destroy();

	constexpr SDL_Window* GetWindow() const { return m_WindowHandle; }

	int GetWidth();
	int GetHeight();

private:
	SDL_Window* m_WindowHandle = nullptr;
	SDL_GLContext m_glContext = nullptr;
};