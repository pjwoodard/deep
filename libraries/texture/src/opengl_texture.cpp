#include "glad/glad.h"
#include "stb_image.h"

#include "texture/opengl_texture.h"

OpenGLTexture::OpenGLTexture()
{
    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load and generate the texture
    //    int32_t width{0};
    //    int32_t height{0};
    //    int32_t nrChannels{0};
    // unsigned char *data = stbi_load("textures/brick.png", &width, &height, &nrChannels, 0);
    // if (data != nullptr)
    // {
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // }
    // else
    // {
    //     puts("Failed to load texture\n");
    // }
    // stbi_image_free(data);
}
