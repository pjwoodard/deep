# Generic test that uses conan libs
add_executable(deep_exe deep_exe.cpp)

set_target_properties(deep_exe PROPERTIES OUTPUT_NAME "deep")

target_link_libraries(
        deep_exe
        PRIVATE
            docopt_s
            fmt::fmt-header-only
            spdlog::spdlog_header_only
            stb::stb
            deep::logger
            deep::math
            deep::shader
            deep::window
            deep::context
            deep::deep
            deep::events
            deep::imgui
            deep::layer
            deep::memory
            deep::vulkan)

if(WIN32)
    target_compile_definitions(
        deep_exe 
        PUBLIC 
            _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)
endif()