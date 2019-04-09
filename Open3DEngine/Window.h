#pragma once



#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#include "Camera.h"

namespace Engine {

	class Window {
	private:

		GLFWwindow *m_Window;
		const char *m_Name;
		GLuint m_Width, m_Height;	
		static Camera camera;
		static double xpos, ypos;
		static double lastX;
		static double lastY;
		static bool keys[1024];
		static float xoffset;
		static float yoffset;
		static float x0;
		static float y0;

	public:
		static void cursor_position_callback(GLFWwindow* window, double xpos , double ypos);
		static void mouse_right_callback(GLFWwindow* window, int button, int action, int mods);
		Window(GLuint Width, GLuint Height, const char *Name);
		~Window();
		bool Init();
		bool Close() const;
		void Update() const;
		void Clear() const;
		GLuint getResX();
		GLuint getResY();
		static float  getOffx();
		static float  getOffy();
		Camera &getCamera();
		
	};
}