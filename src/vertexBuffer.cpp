#include "vertexBuffer.hpp"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &m_ID);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::data(std::vector<float> vertices, BufferTypes type)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), type);
}