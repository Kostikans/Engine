#pragma once


#include "src/Transformation.h"
#include "src/render/buffer/IndexBuffer.h"
#include "src/render/buffer/VertexArray.h"
#include "src/render/buffer/VertexBuffer.h"
#include "src/render/buffer/VertexBufferLayout.h"
#include "src/Window/Window.h"
#include "SimpleLight.h"

namespace Engine
{
	class SimpleObject
	{
	private:

		glm::vec3 m_scale;
		glm::vec3 m_transformation;
		glm::quat m_rotate;
		glm::mat4x4 m_globalTransform;
		const GLsizei size = 290;
		VertexArray VAO;
		VertexBuffer VBO;
		Texturer m_texture;
		GLuint ID;

	public:
		
		SimpleObject(const Texturer &texture);
		void init(const VertexBufferLayout &layout, float texRes);
		void draw(Shader &shader);
		void drawShad(Shader &shader,SimpleLight &lamp);
		void drawShadowMap(Shader &shader,SimpleLight &lamp);
		void rotate(const glm::quat &r);
		void translate(const glm::vec3 &t);
		void scaleObject(const glm::vec3 & s);
		void setGlobalTransform(const glm::mat4x4 &g);
		void add(GLuint ID);
		glm::vec3 GetPos();
	};
}