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
    void init_vulkan();
    void setup_debug_messenger();

    GLFWwindow* window_;
    VkInstance instance_;
    VkDebugUtilsMessengerEXT debugMessenger;
};
}// namespace deep
