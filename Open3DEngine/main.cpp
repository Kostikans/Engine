
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
#include "src/render/Render.h"
#include "src/render/Texture/framebuffer/DepthBuffer.h"
#include "src/item/SimpleLight.h"

using namespace Engine;

const GLuint Width = 1400;
const GLuint Height = 700;
void renderQuad();



int main()
{
	Window window(Width,Height,"MyWindow");
	glewInit();
	Shader DepthShader("src/render/Shader/DepthShader.vs", "src/render/Shader/DepthShader.fs", "src/render/Shader/DepthShader.gs");
	Shader Debug("src/render/Shader/Debug.vs", "src/render/Shader/Debug.fs");
	Shader ShadowShader("src/render/Shader/ShadowMap.vs", "src/render/Shader/ShadowMap.fs");
	Shader lightShader("src/render/Shader/LightShader.vs", "src/render/Shader/LightShader.fs");
	Shader lampShader("src/render/Shader/lamp.vs", "src/render/Shader/lamp.fs");
	Shader screenShader("src/render/Shader/ScreenShader.vs", "src/render/Shader/ScreenShader.fs");
	Texturer texture("a0LBcD.jpg");
	Texturer texture1("laminate.jpg");
	VertexBufferLayout layout;
    layout.push<GLfloat>(3);
	layout.push<GLfloat>(3);
	layout.push<GLfloat>(2);

	SimpleObject cube(texture);
	SimpleObject floar(texture1);
	floar.init(layout,50.0f);
	cube.init(layout,1.0f);
	SimpleLight lamp(texture);
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
	lamp.translate(glm::vec3(1.0f, 2.0f, 1.0f));
	lamp.scaleObject(glm::vec3(0.2f, 0.2f, 0.2f));
	floar.translate(glm::vec3(0.0f, -1.0f, 0.0f));
	floar.scaleObject(glm::vec3(50.0f, 0.1f, 50.0f));

	FrameBuffer frameBuff;
	DepthBuffer depthBuff;
	
	while (!window.Close())
	{
		float lightX = 0.05f * sin(glfwGetTime());
		float lightY = 0.0f;
	    float lightZ = 0.05f * cos(glfwGetTime());
		glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
		
		window.Clear();
		glViewport(0, 0, 2048, 2048);
		depthBuff.Bind();
		window.Clear();
		DepthShader.use();
		lamp.drawShadowMap(DepthShader);
		floar.drawShadowMap(DepthShader, lamp);
		cube.drawShadowMap(DepthShader, lamp);
		depthBuff.UnBind();
		
		glViewport(0, 0, 1400, 700);
		window.Clear();

		frameBuff.Bind();
		window.Clear();

		//lightShader.use();
		//lightShader.use();
		//lightShader.SetUniform3vec("light.position", lamp.GetPos());
		//lightShader.SetUniform3vec("viewPos",window.getViewPos());
		//lightShader.SetUniform3f("material.specular", 0.5f, 0.5f, 0.5f);
		//lightShader.SetUniform1f("material.shininess", 128.0f);
		//lightShader.SetUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
		//lightShader.SetUniform3f("light.diffuse", 0.5f, 0.5f, 0.5f);
		//lightShader.SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);

		ShadowShader.use();
		ShadowShader.SetUniform3vec("lightPos", lamp.GetPos());
		ShadowShader.SetUniform3vec("viewPos", window.getViewPos());
		ShadowShader.SetUniform1i("shadows", 1);
		
		cube.add(depthBuff.GetMapID());
		floar.add(depthBuff.GetMapID());

		
		cube.drawShad(ShadowShader,lamp);
	    floar.drawShad(ShadowShader,lamp);

	
		lampShader.use();
		lamp.draw(lampShader);
		lamp.translate(lightPos);
	
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
