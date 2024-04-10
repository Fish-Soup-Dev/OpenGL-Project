#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture2D::Texture2D()
{
    glGenTextures(1, &m_ID);
    use();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_ID);
}

void Texture2D::use()
{
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture2D::loadImage(const char* imagePath, bool flip)
{
    stbi_set_flip_vertically_on_load(flip);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

    if (data)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    else
        std::cout << "Failed to load texture: " << imagePath << std::endl;

    stbi_image_free(data);
}


Texture2DA::Texture2DA()
{
    glGenTextures(1, &m_ID);
    use();

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture2DA::~Texture2DA()
{
    glDeleteTextures(1, &m_ID);
}

void Texture2DA::use()
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_ID);
}

void Texture2DA::loadImageArray(const char* imagePath, bool flip, glm::vec2 tileSize, glm::vec2 tileCount)
{
    stbi_set_flip_vertically_on_load(flip);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

    int imageCount = tileSize.x * tileSize.y;
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, tileCount.x, tileCount.y, imageCount, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    std::vector<unsigned char> tile(tileCount.x * tileCount.y * nrChannels);
    int tileSizeX = tileCount.x * nrChannels;
    int rowLen    = tileSize.x * tileSizeX;

    for (int iy = 0; iy < tileSize.y; ++ iy)
    {
        for (int ix = 0; ix < tileSize.x; ++ ix)
        {
            unsigned char *ptr = data + iy * rowLen + ix * tileSizeX;

            for (int row = 0; row < tileCount.y; ++ row)
                std::copy(ptr + row * rowLen, ptr + row*rowLen + tileSizeX, tile.begin() + row*tileSizeX);

            int i = iy * tileSize.x + ix;
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, tileCount.x, tileCount.y, 1, GL_RGBA, GL_UNSIGNED_BYTE, tile.data());
        }
    }

    stbi_image_free(data);
}