#pragma once
#include <gl/glew.h>
namespace Engine
{
	class VertexBuffer
	{

	private:
		unsigned int m_RendererID;

	public:
		VertexBuffer();
		~VertexBuffer();

		void push(const GLfloat * data, unsigned int size);
		void Bind() const;
		void Unbind() const;
	};
}
