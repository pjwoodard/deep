#include "logger/logger.h"
#include "vulkan/vulkan_api.h"

using namespace std::literals;

int main()
{
    deep::Logger::info_core("Starting Vulkan Test Application");
    deep::VulkanApi api;
    api.initialize();
    api.run();
    api.destroy();
    return 0;
}
