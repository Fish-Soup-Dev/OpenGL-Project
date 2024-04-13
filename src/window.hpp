#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Window
{
public:
    GLFWwindow* m_window;
    glm::vec2 m_windowSize;

    Window(glm::vec2 size, std::string title);
    ~Window();

    bool isWindowOpen();
    void clear();
    void swap();
    void setCursor(bool mode);
    glm::mat4 getWindowProjection();

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};

#endif