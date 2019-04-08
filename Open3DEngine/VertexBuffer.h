#pragma once


#include <gl/glew.h>

namespace Engine {
	class VertexBuffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_ComponentCount;

	public:
		VertexBuffer(GLfloat *data, GLsizei count, GLuint componentCount = 0);
		void Bind() const;
		void Unbind() const;
	};
}
