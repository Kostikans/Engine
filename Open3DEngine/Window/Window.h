#pragma once

#include <GLFW/glfw3.h>


namespace Engine {
	class Window {
	private:

		GLFWwindow *m_Window;
		const char *m_Name;
		GLuint m_Width, m_Height;
		bool Init();
		
	public:

		Window(GLuint Width, GLuint Height, const char *Name);
		~Window();
		bool Close() const;
		void Update() const;
		void Clear() const;
	};
}