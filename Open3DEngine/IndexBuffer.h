#pragma once


#include <gl/glew.h>

namespace Engine {
	class IndexBuffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_ComponentCount;

	public:
		IndexBuffer(GLushort *data, GLsizei count, GLuint componentCount);
		void Bind() const;
		void Unbind() const;
	};
}
