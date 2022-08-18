add_library(logger src/spd_logger.cpp src/stdout_logger.cpp)
add_library(deep::logger ALIAS logger)

target_include_directories(logger
        PUBLIC
            include/)

target_link_libraries(logger 
    PUBLIC
        spdlog::spdlog
    PRIVATE
        project_warnings
        deep::types)

