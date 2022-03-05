add_library(logger src/spdlog_logger.cpp)
add_library(deep::logger ALIAS logger)

target_include_directories(logger
        PUBLIC
            include/)

target_link_libraries(logger 
    PRIVATE 
        spdlog::spdlog
        deep::types)

