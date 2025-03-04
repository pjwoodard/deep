#include "vulkan/vulkan_api.h"

#include <stdexcept>
#include <utility>
#include <vector>
#include <fmt/format.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace
{
    VkInstance create_vulkan_instance()
    {
        VkInstance instance{};

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount{0};
        const char** glfwExtensions{nullptr};

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS) {
            throw std::runtime_error(fmt::format("failed to create instance: {}!", std::to_underlying(result)));
        }

        return instance;
    }
}

namespace deep
{
VulkanApi::VulkanApi()
{
}

void VulkanApi::initialize()
{
    init_window();
    instance_ = init_vulkan();
}

void VulkanApi::destroy()
{
    vkDestroyInstance(instance_, nullptr);
    glfwDestroyWindow(window_);
    glfwTerminate();    
}

VkInstance VulkanApi::init_vulkan()
{
    return create_vulkan_instance();
}

void VulkanApi::init_window()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window_ = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr); 
}

void VulkanApi::run()
{
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
    }
}
}