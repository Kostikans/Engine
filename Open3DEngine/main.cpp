
#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Window.h"

using namespace Engine;

const GLuint Width = 800;
const GLuint Height = 600;



int main()
{
	Window window(Width, Height, "MyWindow");	

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!window.Close())
	{
		
		
		window.Clear();
		window.Update();
	
	}

	return 0;
}



