#include "SimpleObject.h"
#include <iostream>
namespace Engine
{
	SimpleObject::SimpleObject(const Texturer &texture)
	{
				
		m_texture = texture;
		m_globalTransform = glm::mat4x4(1.0f);
		m_scale = glm::vec3(1.0f);
		m_transformation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_rotate = glm::quat(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 0.0f)));

	}
	void SimpleObject::init(const VertexBufferLayout &layout,float texRes)
	{
		GLfloat vertices[] =
		{
				-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
				0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, texRes, 0.0f,
				0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, texRes, texRes,
				0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, texRes,texRes,
				-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, texRes,
				-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

				-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, texRes, 0.0f,
				0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, texRes, texRes,
				0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, texRes, texRes,
				-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, texRes,
				-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

				-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, texRes, 0.0f,
				-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, texRes,texRes,
				-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, texRes,
				-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, texRes,
				-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, texRes, 0.0f,

				0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, texRes, 0.0f,
				0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, texRes, texRes,
				0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, texRes,
				0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, texRes,
				0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, texRes, 0.0f,

				-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, texRes,
				0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, texRes, texRes,
				0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, texRes, 0.0f,
				0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, texRes, 0.0f,
				-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, texRes,

				-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, texRes,
				0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, texRes, texRes,
				0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, texRes, 0.0f,
				0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, texRes, 0.0f,
				-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
				-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, texRes
		};
		VBO.push(vertices, size);
		VAO.PushLayout(VBO, layout);
	}
	void SimpleObject::draw( Shader &shader)
	{
		shader.use();

	
		glm::mat4x4 modelMatrix;
		modelMatrix = glm::mat4x4(1.0f);
		modelMatrix = glm::translate(modelMatrix, m_transformation);
		modelMatrix = glm::mat4_cast(m_rotate) * modelMatrix;
		modelMatrix = glm::scale(modelMatrix, m_scale);
		modelMatrix = m_globalTransform * modelMatrix;
		shader.SetUniform1i("diffuseTexture", 0);
	
		shader.SetUniformMat4f("model", modelMatrix);
		shader.SetUniformMat4f("projection", Window::GetProjectionMatrix());
		Window::getCamera().draw(shader);
		VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 54);
		
	}
	void SimpleObject::drawShad(Shader & shader, SimpleLight &lamp)
	{
		shader.use();

		m_texture.Bind();
		
		glm::mat4x4 modelMatrix;
		modelMatrix = glm::mat4x4(1.0f);
		modelMatrix = glm::translate(modelMatrix, m_transformation);
		modelMatrix = glm::mat4_cast(m_rotate) * modelMatrix;
		modelMatrix = glm::scale(modelMatrix, m_scale);
		modelMatrix = m_globalTransform * modelMatrix;
		shader.SetUniform3vec("lightPos", lamp.GetPos());
		shader.SetUniformMat4f("model", modelMatrix);
		shader.SetUniformMat4f("projection", Window::GetProjectionMatrix());
		shader.SetUniform1f("farPlane", 100.0f);
		shader.SetUniform1i("diffuseTexture", 0);
		shader.SetUniform1i("depthMap", 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
		Window::getCamera().draw(shader);
		VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 54);
		m_texture.UnBind();
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		VAO.Unbind();
	}
	void SimpleObject::drawShadowMap(Shader &shader,SimpleLight &lamp)
	{
		shader.use();

		glm::mat4x4 modelMatrix;
		modelMatrix = glm::mat4x4(1.0f);
		modelMatrix = glm::translate(modelMatrix, m_transformation);
		modelMatrix = glm::mat4_cast(m_rotate) * modelMatrix;
		modelMatrix = glm::scale(modelMatrix, m_scale);
		modelMatrix = m_globalTransform * modelMatrix;

		glm::vec3 LampPos = lamp.GetPos();
		glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), 1024.0f / 1024.0f, 1.0f, 100.0f);

		std::vector<glm::mat4> shadowTransforms;
	    shadowTransforms.push_back(shadowProj * glm::lookAt(LampPos, LampPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(LampPos, LampPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(LampPos, LampPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(LampPos, LampPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(LampPos, LampPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(LampPos, LampPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

		for (int i = 0; i < 6; i++)
			shader.SetUniformMat4f("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
				
		
		shader.SetUniform1f("farPlane", 100.0f);
		shader.SetUniformMat4f("model", modelMatrix);			 
	 	shader.SetUniform3vec("lightPos", LampPos);

		
		VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 54);
		VAO.Unbind();
	}
	void SimpleObject::rotate(const glm::quat & r)
	{
		m_rotate *= r;
	}
	void SimpleObject::translate(const glm::vec3 & t)
	{
		m_transformation += t;
	}
	void SimpleObject::scaleObject(const glm::vec3 & s)
	{
		m_scale *= s;
	}
	void SimpleObject::setGlobalTransform(const glm::mat4x4 & g)
	{
		m_globalTransform = g;
	}
	void SimpleObject::add(GLuint ID)
	{
		this->ID = ID;
	}
	glm::vec3 SimpleObject::GetPos()
	{
		return m_transformation;
	}
}