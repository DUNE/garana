##############################################################################################
##               garana top-level CMake file                                                ##
##############################################################################################

cmake_minimum_required(VERSION 3.8...3.19)

project(garana VERSION 0.0.1 
                DESCRIPTION "tools for garsoft analysis ( DUNE ND-GAr )"
                LANGUAGES CXX
)

# Defines the CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_BINDIR and many other useful macros.
# See https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Control where libraries and executables are placed during the build.
  # With the following settings executables are placed in <the top level of the
  # build tree>/bin and libraries/archives in <top level of the build tree>/lib.
  # This is particularly useful to run ctests on libraries built on Windows
  # machines: tests, which are executables, are placed in the same folders of
  # dlls, which are treated as executables as well, so that they can properly
  # find the libraries to run. This is a because of missing RPATH on Windows.
  #set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
  #set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
  #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
  
  # Under MSVC, we set CMAKE_DEBUG_POSTFIX to "d" to add a trailing "d" to library
  # built in debug mode. In this Windows user can compile, build and install the
  # library in both Release and Debug configuration avoiding naming clashes in the
  # installation directories.
  if(MSVC)
      set(CMAKE_DEBUG_POSTFIX "d")
  endif()
  
  # To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
  # See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
  # See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)

  if(UNIX)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:\$ORIGIN/../bin:\$ORIGIN")
  endif()

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_C_EXTENSIONS OFF)
  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic -Wno-ignored-qualifiers -Wno-inline")

  #list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

  set(BUILD_SHARED_LIBS ON)

  option(BUILD_TESTING "Create tests using CMake" OFF)
  if(BUILD_TESTING)
      enable_testing()
  endif()

  # Enable RPATH support for installed binaries and libraries
  #include(AddInstallRPATHSupport)
  #add_install_rpath_support(BIN_DIRS "${CMAKE_INSTALL_FULL_BINDIR}"
  #                          LIB_DIRS "${CMAKE_INSTALL_FULL_LIBDIR}"
  #                          INSTALL_NAME_DIR "${CMAKE_INSTALL_FULL_LIBDIR}"
  #                         USE_LINK_PATH)

  # Encourage user to specify a build type (e.g. Release, Debug, etc.), otherwise set it to Release.
  if(NOT CMAKE_CONFIGURATION_TYPES)
      if(NOT CMAKE_BUILD_TYPE)
          message(STATUS "Setting build type to 'Release' as none was specified.")
          set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Release")
      endif()
  endif()

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
endif() #end if top level project directory

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(AddInstallRPATHSupport)
add_install_rpath_support(BIN_DIRS "${CMAKE_INSTALL_FULL_BINDIR}"
                          LIB_DIRS "${CMAKE_INSTALL_FULL_LIBDIR}"
                          INSTALL_NAME_DIR "${CMAKE_INSTALL_FULL_LIBDIR}"
                          USE_LINK_PATH)

# find required package: ROOT
list(APPEND CMAKE_PREFIX_PATH "$ENV{ROOTSYS}")
find_package(ROOT 6.16 CONFIG REQUIRED)
if(ROOT_FOUND)
  message(STATUS "FOUND ROOT :)")
else()
  message(STATUS "ROOT not found!")
endif()

set(BASEPATH "${CMAKE_SOURCE_DIR}")
include_directories("${BASEPATH}")

include(${ROOT_USE_FILE})

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

# Note that if your library depends from other libraries, you are probably
# required to used the install_basic_package_files() DEPENDENCIES option.
include(InstallBasicPackageFiles)
install_basic_package_files(${PROJECT_NAME}
                            VERSION ${${PROJECT_NAME}_VERSION}
                            COMPATIBILITY AnyNewerVersion
                            FIRST_TARGET GaranaDict
                            VARS_PREFIX ${PROJECT_NAME}
                            NO_CHECK_REQUIRED_COMPONENTS_MACRO)
# Add the uninstall target
include(AddUninstallTarget)

# Add integration tests (unit tests for each library should be in each sublibrary directory).
if(BUILD_TESTING)
    add_subdirectory(test)
endif()


#install(TARGETS ${LIBRARY_TARGET_NAME}
#        EXPORT  ${PROJECT_NAME}
#        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
#        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
#        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
#        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_TARGET_NAME}" COMPONENT dev)


#message(STATUS "Created target ${LIBRARY_TARGET_NAME} for export ${PROJECT_NAME}.")


#export(TARGETS GaranaAccessors GaranaBase GaranaProcessors GaranaProducts GaranaDict NAMESPACE garana:: FILE garana.cmake)
#set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
#export(PACKAGE garana)
##
### Packaging support
#set(CPACK_PACKAGE_VENDOR "Chris Hilgenberg")
#set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "tools for garsoft analysis")
#set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
#set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
#set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
##set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENCE")
##set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
#
#set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
#set(CPACK_SOURCE_IGNORE_FILES
#    /.git
#    /.gitignore
#)
#include(CPack)
