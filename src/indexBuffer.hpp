#pragma once
#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <GL/glew.h>

#include <vector>

#include "bufferTypes.hpp"

class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    void bind();
    void data(std::vector<unsigned int> indices, BufferTypes type);

private:
    unsigned int m_ID;
};

#endif