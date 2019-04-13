#pragma once
#include <gl/glew.h>
namespace Engine
{
	class VertexBuffer
	{

	private:
		unsigned int m_RendererID;

	public:
		VertexBuffer(const GLfloat * data, unsigned int size);
		~VertexBuffer();

		
		void Bind() const;
		void Unbind() const;
	};
}
