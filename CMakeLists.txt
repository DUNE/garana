##############################################################################################
##               garana top-level CMake file                                                ##
##############################################################################################

cmake_minimum_required(VERSION 3.14...3.19)

project(garana VERSION 00.00.09
               DESCRIPTION "tools for garsoft analysis ( DUNE ND-GAr )"
               LANGUAGES CXX
)


# cetbuildtools is used by mrb
# and it contains cmake modules
option(BUILD_W_CET "Build with cetbuildtools" OFF )

IF( BUILD_W_CET )

    SET ( CETBUILDTOOLS_VERSION $ENV{CETBUILDTOOLS_VERSION} )
    IF (NOT CETBUILDTOOLS_VERSION)
        MESSAGE (FATAL_ERROR "ERROR: setup cetbuildtools to get the cmake modules")
    ENDIF()

    set( CMAKE_MODULE_PATH $ENV{CANVAS_ROOT_IO_DIR}/Modules
                           $ENV{CETBUILDTOOLS_DIR}/Modules 
                           ${CMAKE_MODULE_PATH})

    include(CetCMakeEnv)
    cet_cmake_env()
    
    # -D_GLIBCXX_USE_NANOSLEEP is needed to make std::this_thread::sleep_for available.
    cet_set_compiler_flags(DIAGS CAUTIOUS 
                           WERROR
                           NO_UNDEFINED
                           EXTRA_FLAGS -pedantic -Wno-unused-local-typedefs
                           EXTRA_CXX_FLAGS -D_GLIBCXX_USE_NANOSLEEP ${ARTDFLAG} -Wno-variadic-macros -fPIC)
    cet_report_compiler_flags()

    find_ups_product( art v1_09_00          )
    find_ups_product( canvas        )
    find_ups_product( cetbuildtools v3_10_00 )
    find_ups_root()

    message(STATUS "ROOTSYS is ${ROOTSYS}")

    # macros
    include(ArtMake)
    include(ArtDictionary)
    include(BuildPlugins)
    include(CetRootCint)

    # ups - table and config files
    add_subdirectory(ups)

    # packaging utility
    include(UseCPack)

#(not using mrb/ups) e.g. installing on personal machine
ELSE()
    # Defines the CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_BINDIR and many other useful macros.
    # See https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
    include(GNUInstallDirs)

    # Control where libraries and executables are placed during the build.
    # With the following settings executables are placed in <the top level of the
    # build tree>/bin and libraries/archives in <top level of the build tree>/lib.
    # This is particularly useful to run ctests on libraries built on Windows
    # machines: tests, which are executables, are placed in the same folders of
    # dlls, which are treated as executables as well, so that they can properly
    # find the libraries to run. This is a because of missing RPATH on Windows.
    #include(${ROOT_USE_FILE})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

    # Only do these if this is the main project, and not if it is included through add_subdirectory
    IF(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    
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
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -gdwarf-4 -O3 -fno-omit-frame-pointer -std=c++17 -Werror -Wall -Wextra -pedantic -Wunused-variable -Wunused-parameter -Wno-unused-local-typedefs -Wno-ignored-qualifiers -Wno-inline -Wno-variadic-macros -fPIC -D_GLIBCXX_USE_NANOSLEEP -Werror=return-type")

    
      set(BUILD_SHARED_LIBS ON)
    
      option(BUILD_TESTING "Create tests using CMake" OFF)
      if(BUILD_TESTING)
          enable_testing()
      endif()
    
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
    ENDIF() #end if top level project directory

    
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
    
    include(AddInstallRPATHSupport)
    add_install_rpath_support(BIN_DIRS "${CMAKE_INSTALL_FULL_BINDIR}"
                              LIB_DIRS "${CMAKE_INSTALL_FULL_LIBDIR}"
                              INSTALL_NAME_DIR "${CMAKE_INSTALL_FULL_LIBDIR}"
                              USE_LINK_PATH)
    

    # find required package: ROOT (needed to make dictionary during build)
    list(APPEND CMAKE_PREFIX_PATH "$ENV{ROOTSYS}") # "$ENV{PYTHONPATH}")
    #find_package(python 2.7 CONFIG REQUIRED)
    #find_package(python 3.9 CONFIG REQUIRED)
    find_package(ROOT 6.22 CONFIG REQUIRED)
    if(ROOT_FOUND)
      message(STATUS "FOUND ROOT :)")
    else()
      message(STATUS "ROOT not found!")
    endif()

    #message(STATUS "Base path is ${CMAKE_SOURCE_DIR}")
    set(BASEPATH "${CMAKE_SOURCE_DIR}")
    include_directories("${BASEPATH}")

    include(${ROOT_USE_FILE})

ENDIF()

# The compiled library code is here
add_subdirectory(garana)

# The executable code is here
add_subdirectory(apps)

IF(NOT BUILD_W_CET)

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

ENDIF() #end if not using cetbuildtools

