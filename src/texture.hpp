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
    Texture2D();
    ~Texture2D();

    void use();
    void loadImage(const char* imagePath, bool flip);

private:
    unsigned int m_ID;
};

class Texture2DA
{
public:
    Texture2DA();
    ~Texture2DA();

    void use();
    void loadImageArray(const char* imagePath, bool flip, glm::vec2 tileSize, glm::vec2 tileCount);

private:
    unsigned int m_ID;
};

class TextureCubeMap
{
public:
    TextureCubeMap();
    ~TextureCubeMap();

    void use();
    void loadImages(std::vector<const char*> imagePaths, bool flip);

private:
    unsigned int m_ID;
};

#endif