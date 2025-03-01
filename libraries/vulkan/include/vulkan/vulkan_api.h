#pragma once

class GLFWwindow;

namespace deep
{

class VulkanApi
{
  public:
    VulkanApi();

    void initialize();
    void destroy(); 
  private:
    void init_window();
    void init_vulkan();
    void main_loop();

    GLFWwindow* window_;
};
}// namespace deep
