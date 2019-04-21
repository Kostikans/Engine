#pragma once


#include <gl/glew.h>
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

namespace Engine {
	class VertexArray
	{
	private:
		GLuint m_BufferID;

	public:
		VertexArray();
		~VertexArray();
		void PushLayout(const VertexBuffer &VBO, const VertexBufferLayout &layout);
		void Bind() const;
		void Unbind() const;
	};
}
