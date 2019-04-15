#include "Window.h"
#include <iostream>


namespace Engine
{
	glm::mat4x4 Window::ProjectionMatrix = glm::mat4x4(1.0f);
	int Window::m_Height, Window::m_Width;
    double  Window::xpos, Window::ypos;
	double Window::lastX = 400;
    double  Window::lastY = 300;
	bool Window::keys[1024];
	double Window::xoffset = 0;
	double Window::yoffset = 0;

	Camera Window::camera;
	CameraWASD Window::Cam3d;
	void Window::cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
	{
	
		if (keys[GLFW_MOUSE_BUTTON_LEFT] == 1)
		{
			
			double xoffset = xpos - lastX;
			double yoffset = ypos - lastY;
			glfwGetCursorPos(window, &xpos, &ypos);
			lastX = xpos;
			lastY = ypos;
	
			Cam3d.rotateFromInput(xoffset, yoffset);
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

	void Window::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
	{
		if (yoffset > 0)
		{
			Cam3d.scaleCamera(1.2f);
		}
		if (yoffset < 0)
		{
			Cam3d.scaleCamera(0.8f);
		}
	}

	void Window::window_size_callback(GLFWwindow * window, int width, int height)
	{
		GLuint Wid = width;
		GLuint hei = height;
		glfwGetWindowSize(window, &width, &height);
		m_Width = width;
		m_Height = height;
		if (Wid != width && hei != height)
		{
			ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)m_Width / (float)m_Height, 0.1f, 1000.0f);
	    }
	
	}

	void Window::framebuffer_size_callback(GLFWwindow * window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	void Window::window_refresh_callback(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
	}
	void Window::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			keys[GLFW_KEY_W] = 1;
		}
		else
			keys[GLFW_KEY_W] = 0;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			keys[GLFW_KEY_S] = 1;
		}
		else
			keys[GLFW_KEY_S] = 0;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			keys[GLFW_KEY_A] = 1;
		}
		else
			keys[GLFW_KEY_A] = 0;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			keys[GLFW_KEY_D] = 1;
		}
		else
			keys[GLFW_KEY_D] = 0;
	}
	void Window::cameraTranslate()
	{
		if (keys[GLFW_KEY_W] == 1)
		{
			glm::vec3 dir = Cam3d.GetDirection();
			Cam3d.translateCamera(glm::vec3(dir.x / 20.0f, dir.y / 20.f, (dir.z / 20.f)));
		}
		if (keys[GLFW_KEY_S] == 1)
		{
			glm::vec3 dir = Cam3d.GetDirection();
			Cam3d.translateCamera(-(glm::vec3(dir.x / 20.0f, dir.y / 20.f, (dir.z / 20.f))));
		}
		if (keys[GLFW_KEY_A] == 1)
		{
			glm::vec3 dir = Cam3d.GetDirection();
			glm::vec3 up = Cam3d.GetUp();
			glm::vec3 kek = glm::normalize(glm::cross(dir, up));
			Cam3d.translateCamera(-(glm::vec3(kek.x / 20.0f, kek.y / 20.0f, kek.z / 20.f)));
		}
		if (keys[GLFW_KEY_D] == 1)
		{
			glm::vec3 dir = Cam3d.GetDirection();
			glm::vec3 up = Cam3d.GetUp();
			glm::vec3 kek = glm::normalize(glm::cross(dir, up));
			Cam3d.translateCamera(glm::vec3(kek.x / 20.0f, kek.y / 20.0f, kek.z / 20.f));
		}
	}
	Window::Window(GLuint Width, GLuint Height, const char *Name)
	{
		m_Height = Height;
		m_Width = Width;
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
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL , NULL);
		
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
		ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)m_Width / (float)m_Height, 0.1f, 1000.0f);

		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_right_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);
		glfwSetWindowSizeCallback(m_Window, window_size_callback);
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		glfwSetWindowRefreshCallback(m_Window, window_refresh_callback);
		glfwSetKeyCallback(m_Window, key_callback);
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

	CameraWASD  &Window::getCamera()
	{
		return Cam3d;
	}

	glm::mat4x4 & Window::GetProjectionMatrix()
	{
		return ProjectionMatrix;
	}
	
}
