#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "src/render/Shader/Shader.h"
#include "src/Camera/OrbitalCamera.h"
#include "src/Camera/CameraWASD.h"
namespace Engine {

	class Window {
	private:
		static glm::mat4x4 ProjectionMatrix;
		GLFWwindow *m_Window;
		GLFWmonitor *m_Monitor;
		const GLFWvidmode* m_Mode;
		const char *m_Name;
		static int m_Width, m_Height;	
		static Camera camera;
		static CameraWASD Cam3d;
		static double xpos, ypos;
		static double lastX;
		static double lastY;
		static bool keys[1024];
		static double xoffset;
		static double yoffset;


	public:
		static void cursor_position_callback(GLFWwindow* window, double xpos , double ypos);
		static void mouse_right_callback(GLFWwindow* window, int button, int action, int mods);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		static void window_size_callback(GLFWwindow* window, int width, int height);
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void window_refresh_callback(GLFWwindow* window);
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void cameraTranslate();
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
		static CameraWASD &getCamera();
		static glm::vec3 getViewPos();
		glm::mat4x4 &GetProjectionMatrix();
		
	};
}