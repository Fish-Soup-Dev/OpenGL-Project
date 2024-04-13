#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "texture.hpp"
#include "text.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "block.hpp"
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"

struct Block
{
    int type;
};

int main()
{
    Window window(glm::vec2(1280, 720), "Window");
    //window.setCursor(false);

    Text text;
    text.loadFont("fonts/8bitPlus8-Regular.ttf");

    double previousTime = glfwGetTime();
    int frameCount = 0;
    int fps = 1;

    glm::mat4 projection;

    int chunkSize = 16;
    std::vector<Block> blocks(chunkSize * chunkSize * chunkSize);
    std::fill(blocks.begin(), blocks.end(), Block({0}));

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    
    Texture2DA textureArray;
    textureArray.loadImageArray("assets/TextureAtlas.png", true, glm::vec2(16, 16), glm::vec2(8, 8));

    Shader textureShader;
    textureShader.load("shaders/texture.vert", "shaders/texture.frag");
    textureShader.setInt("texture1", 0);

    VertexBuffer textureVBO;
    IndexBuffer textureEBO;

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);

    textureVBO.data(vertices, STATIC);
    textureEBO.data(indices, STATIC);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // type attribute
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f));

    std::chrono::steady_clock::time_point lastUpdate;
    float deltaTime;
    float speed = 4.0f;
    float sensitivity = 0.1f;

    double xpos, ypos;
    float lastx = 0, lasty = 0;

    std::vector<const char*> skyboxFiles
    {
        "assets/SkyboxSides.png",
        "assets/SkyboxSides.png",
        "assets/SkyboxTop.png",
        "assets/SkyboxBottom.png",
        "assets/SkyboxSides.png",
        "assets/SkyboxSides.png"
    };

    TextureCubeMap skybox;
    skybox.loadImages(skyboxFiles, true);

    while(!window.isWindowOpen())
    {
        auto now = std::chrono::steady_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
        lastUpdate = now;

        if(glfwGetKey(window.m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window.m_window, true);
        else if (glfwGetKey(window.m_window, GLFW_KEY_W) == GLFW_PRESS)
            camera.setPosition(camera.getPosition() + camera.getFront() * (speed * deltaTime));
        else if (glfwGetKey(window.m_window, GLFW_KEY_S) == GLFW_PRESS)
            camera.setPosition(camera.getPosition() - camera.getFront() * (speed * deltaTime));
        else if (glfwGetKey(window.m_window, GLFW_KEY_A) == GLFW_PRESS)
            camera.setPosition(camera.getPosition() - camera.getRight() * (speed * deltaTime));
        else if (glfwGetKey(window.m_window, GLFW_KEY_D) == GLFW_PRESS)
            camera.setPosition(camera.getPosition() + camera.getRight() * (speed * deltaTime));

        glfwGetCursorPos(window.m_window, &xpos, &ypos);
        camera.setRotation(camera.getRotation() + glm::vec3((xpos - lastx) * sensitivity, (lasty - ypos) * sensitivity, 0.0f));
        lastx = xpos;
        lasty = ypos;

        window.clear();

        double currentTime = glfwGetTime();
        frameCount++;

        if ( currentTime - previousTime >= 1.0 )
        {
            fps = frameCount;
            frameCount = 0;
            previousTime = currentTime;
        }

        textureArray.use();

        projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window.m_windowSize.x) / static_cast<float>(window.m_windowSize.y), 0.1f, 100.0f);
        textureShader.use();
        textureShader.setMat4("projection", projection);
        textureShader.setMat4("view", camera.getViewMatrix());
        glm::mat4 model = glm::mat4(1.0f);
        textureShader.setMat4("model", model);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        text.renderText(window.getWindowProjection(), "FPS " + std::to_string(fps), 25.0f, window.m_windowSize.y - 40.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

        window.swap();
    }

    return(EXIT_SUCCESS);
}