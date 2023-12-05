add_library(logger
        src/spd_logger.cpp
        src/stdout_logger.cpp)

add_library(deep::logger ALIAS logger)

target_include_directories(logger
    PUBLIC
        include/
)

target_link_libraries(logger 
    PUBLIC
        spdlog::spdlog_header_only
        deep::types
    PRIVATE
        project_warnings
)

target_compile_features(logger PUBLIC cxx_std_20)

if(WIN32)
    target_compile_definitions(
        logger 
        PUBLIC 
            _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
          _DISABLE_VECTOR_ANNOTATION=1
          _DISABLE_STRING_ANNOTATION=1)
endif()