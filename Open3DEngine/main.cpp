
#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Window.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace Engine;

const GLuint Width = 800;
const GLuint Height = 600;



int main()
{
	Window window(Width, Height, "MyWindow");

	glewInit();
	Shader ourShader("BasicShader.vs", "BasicShader.fs");

	GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	-0.5f,  0.5f, -0.5f,  
	-0.5f, -0.5f, -0.5f,  

	-0.5f, -0.5f,  0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f,  
	 0.5f,  0.5f,  0.5f,  
	-0.5f,  0.5f,  0.5f,  
	-0.5f, -0.5f,  0.5f, 

	-0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f, -0.5f, 
	-0.5f, -0.5f, -0.5f,  
	-0.5f, -0.5f, -0.5f, 
	-0.5f, -0.5f,  0.5f,  
	-0.5f,  0.5f,  0.5f, 

	 0.5f,  0.5f,  0.5f,  
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f,  

	-0.5f, -0.5f, -0.5f,  
	 0.5f, -0.5f, -0.5f,  
	 0.5f, -0.5f,  0.5f,  
	 0.5f, -0.5f,  0.5f,  
	-0.5f, -0.5f,  0.5f,  
	-0.5f, -0.5f, -0.5f,  

	-0.5f,  0.5f, -0.5f,  
	 0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f,  0.5f,  
	 0.5f,  0.5f,  0.5f,  
	-0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f, -0.5f,  
	};

	GLsizei size = 180;
	VertexBuffer VBO(vertices, size);
	VertexBufferLayout layout;
	layout.push<GLfloat>(3);
	VertexArray VAO;
	VAO.PushLayout(VBO, layout);


	
	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!window.Close())
	{
		window.Clear();
		ourShader.use();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f); 
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)Width / (float)Height, 0.1f, 100.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		float angle = 40.0f;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.SetUniformMat4f("projection", projection);
		ourShader.SetUniformMat4f("view", view);
		ourShader.SetUniformMat4f("model", model);

		
		VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		window.Update();
	
	}

	return 0;
}



