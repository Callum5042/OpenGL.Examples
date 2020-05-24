
#include "MainWindow.h"
#include <SDL_messagebox.h>

MainWindow::MainWindow() 
{
}

MainWindow::~MainWindow()
{
	Destroy();
}

bool MainWindow::Create(std::string&& title, int width, int height)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	// Create Window
	m_WindowHandle = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	if (m_WindowHandle == nullptr)
	{
		SDL_ShowSimpleMessageBox(NULL, "Error", "SDL_CreateWindow failed!", nullptr);
		return false;
	}

	// Create GL Context
	m_glContext = SDL_GL_CreateContext(reinterpret_cast<SDL_Window*>(m_WindowHandle));
	if (m_glContext == nullptr)
	{
		SDL_ShowSimpleMessageBox(NULL, "Error", "SDL_GL_CreateContext failed!", nullptr);
		return false;
	}

	return true;
}

void MainWindow::Destroy()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_WindowHandle);
}

int MainWindow::GetWidth()
{
	int width = 0;
	SDL_GetWindowSize(m_WindowHandle, &width, nullptr);
	return width;
}

int MainWindow::GetHeight()
{
	int height = 0;
	SDL_GetWindowSize(m_WindowHandle, nullptr, &height);
	return height;
}