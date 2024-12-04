#include "vulkan/vulkan_api.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace deep
{
void VulkanApi::initialize()
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}
}