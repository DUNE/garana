
cmake_minimum_required(VERSION 3.8...3.19)

# Project name and a few useful settings. Other commands can pick up the results
project(garana VERSION 1.0.0 
                DESCRIPTION "analysis tools for garsoft analysis"
                LANGUAGES CXX
)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  if(UNIX)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN/../bin:\$ORIGIN")
  endif()

  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app
  # Note this needs to be done in the main CMakeLists
  # since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

  # Docs only available if this is the main app
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

set(BUILD_SHARED_LIBS ON)

# find required package: ROOT
list(APPEND CMAKE_PREFIX_PATH "$ENV{ROOTSYS}")
find_package(ROOT 6.16 CONFIG REQUIRED)
if(ROOT_FOUND)
  message(STATUS "FOUND ROOT :)")
else()
  message(STATUS "ROOT not found!")
endif()

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(BUILD_SHARED_LIBS ON)
set(CMAKE_CXX_FLAGS_INIT "-Wall")

set(BASEPATH "${CMAKE_SOURCE_DIR}")
include_directories("${BASEPATH}")

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
#if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
#   AND BUILD_TESTING)
#  add_subdirectory(tests)
#endif()
