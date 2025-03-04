#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class GLFWwindow;

namespace deep
{

class VulkanApi
{
  public:
    VulkanApi();

    void run();
    void initialize();
    void destroy();

  private:
    void init_window();
    VkInstance init_vulkan();

    GLFWwindow *window_;
    VkInstance instance_;
};
}// namespace deep
