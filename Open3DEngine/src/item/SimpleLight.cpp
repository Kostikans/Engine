#include "src/item/SimpleLight.h"
#include <iostream>
namespace Engine
{
	SimpleLight::SimpleLight()
	{
	}
	SimpleLight::SimpleLight(const Texturer &texture)
	{
		
		m_texture = texture;
		m_globalTransform = glm::mat4x4(1.0f);
		m_scale = glm::vec3(1.0f);
		m_transformation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_rotate = glm::quat(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 0.0f)));

	
	}
	void  SimpleLight::init(const VertexBufferLayout &layout, float texRes)
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
	void  SimpleLight::draw(Shader &shader)
	{
		shader.use();
		m_texture.Bind();
		glm::mat4x4 modelMatrix;
		modelMatrix = glm::mat4x4(1.0f);
		modelMatrix = glm::translate(modelMatrix, m_transformation);
		modelMatrix = glm::mat4_cast(m_rotate) * modelMatrix;
		modelMatrix = glm::scale(modelMatrix, m_scale);
		modelMatrix = m_globalTransform * modelMatrix;

		shader.SetUniformMat4f("model", modelMatrix);
		shader.SetUniformMat4f("projection", Window::GetProjectionMatrix());
		Window::getCamera().draw(shader);
		VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 54);
		m_texture.UnBind();
		VAO.Unbind();
	}
	void  SimpleLight::drawShadowMap(Shader &shader)
	{
		shader.use();


		glm::mat4x4 modelMatrix;
		modelMatrix = glm::mat4x4(1.0f);
		modelMatrix = glm::translate(modelMatrix, m_transformation);
		modelMatrix = glm::mat4_cast(m_rotate) * modelMatrix;
		modelMatrix = glm::scale(modelMatrix, m_scale);
		modelMatrix = m_globalTransform * modelMatrix;


		glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), 1024.0f / 1024.0f, 1.0f, 100.0f);
		std::vector<glm::mat4> shadowTransforms;
		shadowTransforms.push_back(shadowProj * glm::lookAt(m_transformation, m_transformation + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(m_transformation, m_transformation + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(m_transformation, m_transformation + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(m_transformation, m_transformation + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(m_transformation, m_transformation + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(m_transformation, m_transformation + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

		for (int i = 0; i < 6; ++i)
			shader.SetUniformMat4f("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);

		shader.SetUniform1f("farPlane", 100.0f);
		shader.SetUniformMat4f("model", modelMatrix);
		shader.SetUniform3vec("lightPos", m_transformation);
		
		VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 54);
	
	}
	void  SimpleLight::rotate(const glm::quat & r)
	{
		m_rotate *= r;
	}
	void  SimpleLight::translate(const glm::vec3 & t)
	{
		m_transformation += t;
	}
	void  SimpleLight::scaleObject(const glm::vec3 & s)
	{
		m_scale *= s;
	}
	void  SimpleLight::setGlobalTransform(const glm::mat4x4 & g)
	{
		m_globalTransform = g;
	}
	glm::vec3  SimpleLight::GetPos()
	{
		return m_transformation;
	}
}