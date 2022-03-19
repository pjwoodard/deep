macro(run_conan)
  # Download automatically, you can also just copy the conan.cmake file
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(
      STATUS
        "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(
      DOWNLOAD
      "https://raw.githubusercontent.com/conan-io/cmake-conan/release/0.17/conan.cmake"
      "${CMAKE_BINARY_DIR}/conan.cmake"
      TLS_VERIFY ON)
  endif()

  set(ENV{CONAN_REVISIONS_ENABLED} 1)
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

  include(${CMAKE_BINARY_DIR}/conan.cmake)

  # Add (or remove) remotes as needed
  # conan_add_remote(NAME conan-center URL https://conan.bintray.com)
  conan_add_remote(NAME cci URL https://center.conan.io INDEX 0)
  conan_add_remote(
    NAME bincrafters URL
    https://bincrafters.jfrog.io/artifactory/api/conan/public-conan)

  # For multi configuration generators, like VS and XCode
  if(NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Single configuration build!")
    set(LIST_OF_BUILD_TYPES ${CMAKE_BUILD_TYPE})
  else()
    message(STATUS "Multi-configuration build: '${CMAKE_CONFIGURATION_TYPES}'!")
    set(LIST_OF_BUILD_TYPES ${CMAKE_CONFIGURATION_TYPES})
  endif()

  foreach(TYPE ${LIST_OF_BUILD_TYPES})
    message(STATUS "Running Conan for build type '${TYPE}'")

    # Detects current build settings to pass into conan
    conan_cmake_autodetect(settings BUILD_TYPE ${TYPE})
    
    if("${settings}" STREQUAL "arch=x86_64;build_type=Debug;compiler=Visual Studio;compiler.version=17;compiler.runtime=MDd") 
      set(settings "arch=x86_64;build_type=Debug;compiler=msvc;compiler.version=193;compiler.runtime=dynamic")
    elseif("${settings}" STREQUAL "arch=x86_64;build_type=Debug;compiler=Visual Studio;compiler.version=17;compiler.runtime=MTd")
      set(settings "arch=x86_64;build_type=Debug;compiler=msvc;compiler.version=193;compiler.runtime=static")
    elseif("${settings}" STREQUAL "arch=x86_64;build_type=Release;compiler=Visual Studio;compiler.version=17;compiler.runtime=MD")
      set(settings "arch=x86_64;build_type=Release;compiler=msvc;compiler.version=193;compiler.runtime=dynamic")
    elseif("${settings}" STREQUAL "arch=x86_64;build_type=Release;compiler=Visual Studio;compiler.version=17;compiler.runtime=MT")
      set(settings "arch=x86_64;build_type=Release;compiler=msvc;compiler.version=193;compiler.runtime=static")
    elseif("${settings}" STREQUAL "arch=x86_64;build_type=MinSizeRel;compiler=Visual Studio;compiler.version=17;compiler.runtime=MD")
      set(settings "arch=x86_64;build_type=MinSizeRel;compiler=msvc;compiler.version=193;compiler.runtime=dynamic")
    elseif("${settings}" STREQUAL "arch=x86_64;build_type=MinSizeRel;compiler=Visual Studio;compiler.version=17;compiler.runtime=MT")
      set(settings "arch=x86_64;build_type=MinSizeRel;compiler=msvc;compiler.version=193;compiler.runtime=static")
    elseif("${settings}" STREQUAL "arch=x86_64;build_type=RelWithDebInfo;compiler=Visual Studio;compiler.version=17;compiler.runtime=MD")
      set(settings "arch=x86_64;build_type=RelWithDebInfo;compiler=msvc;compiler.version=193;compiler.runtime=dynamic")
    elseif("${settings}" STREQUAL "arch=x86_64;build_type=RelWithDebInfo;compiler=Visual Studio;compiler.version=17;compiler.runtime=MT")
      set(settings "arch=x86_64;build_type=RelWithDebInfo;compiler=msvc;compiler.version=193;compiler.runtime=static")
    endif()

    # PATH_OR_REFERENCE ${CMAKE_SOURCE_DIR} is used to tell conan to process
    # the external "conanfile.py" provided with the project
    # Alternatively a conanfile.txt could be used 
    conan_cmake_install(
      PATH_OR_REFERENCE
      ${CMAKE_SOURCE_DIR}
      BUILD
      missing
      SETTINGS
      ${settings})
  endforeach()

endmacro()
