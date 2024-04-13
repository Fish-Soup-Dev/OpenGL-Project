#pragma once
#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <GL/glew.h>

#include <vector>

#include "bufferTypes.hpp"

class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void bind();
    void data(std::vector<float> vertices, BufferTypes type);

public:
    unsigned int m_ID;
};

#endif