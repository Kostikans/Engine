#include "Window.h"
#include <iostream>

Engine::Window::Window(GLuint Width, GLuint Height, const char *Name)
{
	m_Width = Width;
	m_Height = Height;
	m_Name = Name;
	if (!Init())
	{
		glfwTerminate();
	}
}

Engine::Window::~Window()
{
	if (m_Window)
	{
		glfwDestroyWindow(m_Window);
	}
}

bool Engine::Window::Init()
{
	if (!glfwInit())
	{
		std::cout << "failed to initialize GLFW" << std::endl;
		return false;
	}
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		std::cout << "Failed to create GLFW Window" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(m_Window);
	return true;
}

bool Engine::Window::Close() const
{
	return glfwWindowShouldClose(m_Window);
}

void Engine::Window::Update() const
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Engine::Window::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
}


