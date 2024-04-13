#include "indexBuffer.hpp"

IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &m_ID);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

void IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::data(std::vector<unsigned int> indices, BufferTypes type)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), type);
}