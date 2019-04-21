
#include <iostream>
#include <GL/glew.h>
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
#include <src/Assimp/Model.h>
#include "src/item/SimpleObject.h"
#include "src/render/Texture/framebuffer/Framebuffer.h"

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
	Shader screenShader("src/render/Shader/ScreenShader.vs", "src/render/Shader/ScreenShader.fs");
	Texturer texture("a0LBcD.jpg");
	Texturer texture1("laminate.jpg");
	VertexBufferLayout layout;
    layout.push<GLfloat>(3);
	layout.push<GLfloat>(3);
	layout.push<GLfloat>(2);

	SimpleObject cube;
	SimpleObject floar;
	floar.init(layout,50.0f);
	cube.init(layout,1.0f);
	SimpleObject lamp;
	lamp.init(layout,1.0f);
	window.getCamera().translate(glm::vec3(0.0f, 0.0f, -5.0f));

	float quadVertices[] = { 
	   -1.0f,  1.0f,  0.0f, 1.0f,
	   -1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

	   -1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glEnable(GL_DEPTH_TEST);
	cube.translate(glm::vec3(4.0f, 0.0f, 4.0f));
	lamp.translate(glm::vec3(0.0f, 2.0f, 0.0f));
	lamp.scaleObject(glm::vec3(0.2f,0.2f,0.2f));
	floar.translate(glm::vec3(0.0f, -1.0f, 0.0f));
	floar.scaleObject(glm::vec3(50.0f, 0.1f, 50.0f));

	FrameBuffer frameBuff;
	while (!window.Close())
	{
		float lightX = 0.1f * sin(glfwGetTime());
		float lightY = 0.0f;
		float lightZ = 0.1f * cos(glfwGetTime());
		glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);

		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 1000.0f);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;

		frameBuff.Bind();	
		window.Clear();

		lightShader.use();
		lightShader.SetUniform3vec("light.position", lamp.GetPos());
		lightShader.SetUniform3vec("viewPos",window.getViewPos());
		lightShader.SetUniform3f("material.specular", 0.5f, 0.5f, 0.5f);
		lightShader.SetUniform1f("material.shininess", 32.0f);
		lightShader.SetUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
		lightShader.SetUniform3f("light.diffuse", 0.5f, 0.5f, 0.5f);
		lightShader.SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
		lightShader.SetUniformMat4f("projection", window.GetProjectionMatrix());

		window.getCamera().draw(lightShader);

		cube.draw(lightShader,texture);
		floar.draw(lightShader,texture1);
	
		
		lampShader.use();
		lamp.translate(lightPos);

		lampShader.SetUniformMat4f("projection", window.GetProjectionMatrix());
		window.getCamera().draw(lampShader);
		lamp.draw(lampShader,texture);

		frameBuff.MultiSample();
		frameBuff.UnBind();
		window.Clear();

		screenShader.use();
		glBindVertexArray(quadVAO);
		frameBuff.Bindtex();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.cameraTranslate();
		window.Update();
	}
	return 0;
}



