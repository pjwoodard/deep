find_package(fmt)
find_package(spdlog)
find_package(docopt)
find_package(stb)
find_package(imgui)

# Generic test that uses conan libs
add_executable(deep_exe deep_exe.cpp)

set_target_properties(deep_exe PROPERTIES OUTPUT_NAME "deep")

target_link_libraries(
        deep_exe
        PRIVATE
            project_options
            project_warnings
            docopt::docopt
            fmt::fmt
            spdlog::spdlog
            stb::stb
            deep::logger
            deep::math
            deep::shader
            deep::window
            deep::context
            deep::deep
            deep::events
            deep::layer)
