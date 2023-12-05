add_library(window src/glfw_window.cpp)
add_library(deep::window ALIAS window)

target_include_directories(window
        PUBLIC include/
        PRIVATE ${CMAKE_SOURCE_DIR}/resources)

target_link_libraries(window
        PUBLIC
            myproject_warnings
            myproject_options
            glfw
            glad::glad
            deep::context
            deep::math
            deep::shader
            deep::texture
            deep::logger
            deep::types
            deep::events
        )
