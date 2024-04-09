#pragma once
#ifndef TEXT_HPP
#define TEXT_HPP

#include <iostream>
#include <map>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "shader.hpp"

struct Character
{
    unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};

class Text
{
public:
    Text();
    ~Text();

    void loadFont(const char* fontPath);
    void renderText(glm::mat4 projection, std::string text, float x, float y, float scale, glm::vec3 color);

private:
    Shader shader;
    FT_Library m_ft;
    FT_Face m_face;
    unsigned int VAO, VBO;
    std::map<char, Character> m_characters;
};

#endif