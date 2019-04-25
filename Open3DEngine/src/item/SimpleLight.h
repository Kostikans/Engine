#pragma once


#include "src/Transformation.h"
#include "src/render/buffer/IndexBuffer.h"
#include "src/render/buffer/VertexArray.h"
#include "src/render/buffer/VertexBuffer.h"
#include "src/render/buffer/VertexBufferLayout.h"
#include "src/Window/Window.h"

namespace Engine
{
	class SimpleLight
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
		

	public:
		SimpleLight();
		SimpleLight(const Texturer &texture);
		void init(const VertexBufferLayout &layout, float texRes);
		void draw(Shader &shader);
		void drawShadowMap(Shader &shader);
		void rotate(const glm::quat &r);
		void translate(const glm::vec3 &t);
		void scaleObject(const glm::vec3 & s);
		void setGlobalTransform(const glm::mat4x4 &g);
		glm::vec3 GetPos();
	};
}