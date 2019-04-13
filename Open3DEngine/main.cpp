
#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "src/Window/Window.h"
#include "src/render/buffer/VertexBuffer.h"
#include "src/render/buffer/VertexBufferLayout.h"
#include "src/render/buffer/VertexArray.h"
#include "src/render/buffer/IndexBuffer.h"
#include "src/render/Shader/Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "src/Camera/OrbitalCamera.h"
#include "src/render/Texture/Texture.h"

using namespace Engine;

const GLuint Width = 1400;
const GLuint Height = 700;




int main()
{
	Window window(Width,Height,"MyWindow");

	glewInit();
	Shader ourShader("src/render/Shader/BasicShader.vs", "src/render/Shader/BasicShader.fs");
	Shader lightShader("src/render/Shader/LightShader.vs", "src/render/Shader/LightShader.fs");
	Shader lampShader("src/render/Shader/lamp.vs", "src/render/Shader/lamp.fs");

	GLfloat vertices[] = {
		 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	GLsizei size = 290;
	VertexBuffer VBO(vertices, size);
	VertexBufferLayout layout;
	layout.push<GLfloat>(3);
	layout.push<GLfloat>(3);
	layout.push<GLfloat>(2);
	VertexArray VAO;
	VAO.PushLayout(VBO, layout);

	VertexBufferLayout Lamplayout;
	Lamplayout.push<GLfloat>(3);
	Lamplayout.push<GLfloat>(3);
	Lamplayout.push<GLfloat>(2);
	VertexArray VAOlamp;
	VAOlamp.PushLayout(VBO, Lamplayout);

	window.getCamera().translateCamera(glm::vec3(0.0f, 0.0f, -5.0f));
	Texture texture("a0LBcD.jpg");

	glEnable(GL_DEPTH_TEST);
	lightShader.use();
	
	while (!window.Close())
	{
		float lightX = 2.0f * sin(glfwGetTime());
		float lightY = 0.0f;
		float lightZ = 1.5f * cos(glfwGetTime());
		glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
		window.Clear();
		lightShader.use();
		texture.Bind();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
		glm::vec3 viewPos = (glm::inverse(window.getCamera().GetViewMatrix()))[3];
		glm::mat4 model = glm::mat4(1.0f);
		
		lightShader.SetUniform3f("light.position", lightPos.x, lightPos.y, lightPos.z);
		lightShader.SetUniform3f("viewPos", viewPos.x, viewPos.y, viewPos.z);
		lightShader.SetUniform3f("material.specular", 0.5f, 0.5f, 0.5f);
		lightShader.SetUniform1f("material.shininess", 64.0f);
		lightShader.SetUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
		lightShader.SetUniform3f("light.diffuse", 0.5f, 0.5f, 0.5f);
		lightShader.SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
		

		lightShader.SetUniform1i("material.diffuse", 0);
		lightShader.SetUniformMat4f("projection", window.GetProjectionMatrix());
		lightShader.SetUniformMat4f("model", model);
		window.getCamera().draw(lightShader);
		
	
		VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 54);

		lampShader.use();
		lampShader.SetUniformMat4f("projection", window.GetProjectionMatrix());
		window.getCamera().draw(lampShader);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); 
		lampShader.SetUniformMat4f("model", model);

		VAOlamp.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 54);
		
		window.Update();
	}
	return 0;
}



