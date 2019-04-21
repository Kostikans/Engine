#include "SimpleObject.h"

namespace Engine
{
	SimpleObject::SimpleObject()
	{
		
		m_globalTransform = glm::mat4x4(1.0f);
		m_scale = glm::vec3(1.0f);
		m_transformation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_rotate = glm::quat(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 0.0f)));
	}
	void SimpleObject::init(VertexBufferLayout layout,float texRes)
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
	void SimpleObject::draw(Shader & shader,Texturer texture)
	{
		shader.use();

		texture.Bind();
		glm::mat4x4 modelMatrix;
		modelMatrix = glm::mat4x4(1.0f);
		modelMatrix = glm::translate(modelMatrix, m_transformation);
		modelMatrix = glm::mat4_cast(m_rotate) * modelMatrix;
		modelMatrix = glm::scale(modelMatrix, m_scale);
		modelMatrix = m_globalTransform * modelMatrix;
		shader.SetUniform1i("material.diffuse", 0);
		shader.SetUniformMat4f("model", modelMatrix);
		VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 54);
		texture.UnBind();
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
	glm::vec3 SimpleObject::GetPos()
	{
		return m_transformation;
	}
}