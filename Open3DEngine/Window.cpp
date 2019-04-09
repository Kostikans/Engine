#include "Window.h"
#include <iostream>


namespace Engine
{
   
    double  Window::xpos, Window::ypos;
	double Window::lastX = 400;
    double  Window::lastY = 300;
	bool Window::keys[1024];
	float Window::xoffset = 0;
	float Window::yoffset = 0;
	float Window::x0 = 0;
	float Window::y0 = 0;
	Camera Window::camera;

	void Window::cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
	{
		
		if (keys[GLFW_MOUSE_BUTTON_LEFT] == 1)
		{
			
			float xoffset = xpos - lastX;
			float yoffset = ypos - lastY;
			glfwGetCursorPos(window, &xpos, &ypos);
			lastX = xpos;
			lastY = ypos;
			x0 = xoffset;
			y0 = yoffset;
			std::cout << x0 << ' ' << y0 << std::endl;
			camera.rotateFromInput(xoffset, yoffset);
		}
	
	}

	void Window::mouse_right_callback(GLFWwindow * window, int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			keys[GLFW_MOUSE_BUTTON_LEFT] = 1;
			glfwGetCursorPos(window, &xpos, &ypos);
			lastX = xpos;
			lastY = ypos;
		}
		else
			keys[GLFW_MOUSE_BUTTON_LEFT] = 0;
	}

	Window::Window(GLuint Width, GLuint Height, const char *Name)
	{
		m_Width = Width;
		m_Height = Height;
		m_Name = Name;
		if (!Init())
		{
			glfwTerminate();
		}
	}

	Window::~Window()
	{
		if (m_Window)
		{
			glfwDestroyWindow(m_Window);
		}
	}

	bool Window::Init()
	{
		if (!glfwInit())
		{
			std::cout << "failed to initialize GLFW" << std::endl;
			return false;
		}

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "Failed to create GLFW Window" << std::endl;
			return false;
		}
		
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_right_callback);
		glfwMakeContextCurrent(m_Window);
		return true;
	}

	bool Window::Close() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::Update() const
	{
		
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	GLuint Window::getResX()
	{
		return m_Width;
	}

	GLuint Window::getResY()
	{
		return m_Height;
	}
	float Window::getOffx()
	{
		return x0;
	}
	float Window::getOffy()
	{
		return y0;
	}

	Camera  &Window::getCamera()
	{
		return camera;
	}
	
}