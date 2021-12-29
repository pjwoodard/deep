option(CPP_STARTER_USE_QT "Enable compilation of QT sample" OFF)

# qt
if(CPP_STARTER_USE_QT)
  message("Using Qt")
  add_subdirectory(qt)
endif()

find_package(fmt)
find_package(spdlog)
find_package(docopt)
find_package(stb)

# Generic test that uses conan libs
add_executable(deep deep.cpp)
target_link_libraries(
  deep
  PRIVATE docopt::docopt
          fmt::fmt
          spdlog::spdlog
          stb::stb
          deep::math
          deep::shader
          deep::window
          deep::context)
