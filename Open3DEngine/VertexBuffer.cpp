#include "VertexBuffer.h"
#include <gl/glew.h>


Engine::VertexBuffer::VertexBuffer(const GLfloat *data, unsigned int size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat) , data, GL_STATIC_DRAW);
}
Engine::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}
void Engine::VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}
void Engine::VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

