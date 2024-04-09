#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "shader.hpp"
#include "text.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "block.hpp"

struct Block
{
    int type;
};

int main()
{
    Window window(glm::vec2(1280, 720), "Window");

    glfwSetInputMode(window.m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

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

    

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
    
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    stbi_set_flip_vertically_on_load(true);  

    int width, height, nrChannels;
    unsigned char *data = stbi_load("assets/TextureAtlas.png", &width, &height, &nrChannels, 0);

    if (data)
    {
        int tileW = 16;           // number of pixels in a row of 1 tile
        int tileH = 16;           // number of pixels in a column of 1 tile
        int channels = 4;         // 4 for RGBA

        int tilesX = 8;
        int tilesY = 8;
        int imageCount = tilesX * tilesY;

        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, tileW, tileH, imageCount, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        std::vector<unsigned char> tile(tileW * tileH * channels);
        int tileSizeX = tileW * channels;
        int rowLen    = tilesX * tileSizeX;

        for (int iy = 0; iy < tilesY; ++ iy)
        {
            for (int ix = 0; ix < tilesX; ++ ix)
            {
                unsigned char *ptr = data + iy*rowLen + ix*tileSizeX;
                for (int row = 0; row < tileH; ++ row)
                    std::copy(ptr + row*rowLen, ptr + row*rowLen + tileSizeX,
                            tile.begin() + row*tileSizeX);


                int i = iy * tilesX + ix;
                glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, tileW, tileH, 1, GL_RGBA, GL_UNSIGNED_BYTE, tile.data());
            }
        }
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    Shader textureShader;
    textureShader.load("shaders/texture.vert", "shaders/texture.frag");
    textureShader.setInt("texture1", 0);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);

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

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

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