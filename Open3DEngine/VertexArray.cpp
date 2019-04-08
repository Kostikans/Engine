#include "VertexArray.h"

Engine::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_BufferID);
}

void Engine::VertexArray::PushLayout(const VertexBuffer &VBO, const VertexBufferLayout &layout)
{
	Bind();
	VBO.Bind();
	const auto &elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto &element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeofType(element.type);
	}
}
void Engine::VertexArray::Bind() const
{
	glBindVertexArray(m_BufferID);
}

void Engine::VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
