#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Texture2D
{
public:
    unsigned int m_ID;

    Texture2D();
    ~Texture2D();

    void use();
    void loadImage(const char* imagePath, bool flip);
};

class Texture2DA
{
public:
    unsigned int m_ID;

    Texture2DA();
    ~Texture2DA();

    void use();
    void loadImageArray(const char* imagePath, bool flip, glm::vec2 tileSize, glm::vec2 tileCount);
};


#endif