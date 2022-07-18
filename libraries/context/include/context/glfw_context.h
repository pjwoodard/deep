#pragma once

#include <GLFW/glfw3.h>

namespace GlfwContext
{
    [[maybe_unused]] static void init_glfw()
    {
        const bool init_successful = glfwInit() == GLFW_TRUE;
        assert(init_successful);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }
}

