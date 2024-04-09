#pragma once
#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int m_ID;

    Shader();
    ~Shader();
    
    void use();
    void load(const char* vertexPath, const char* fragmentPath);

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
};

#endif