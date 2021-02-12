
# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")

set(HEADER_DIR "${PROJECT_SOURCE_DIR}/include/garana/Accessors")
set(HEADER_LIST 
      "${HEADER_DIR}/HeaderTree.h"
      "${HEADER_DIR}/FlatGenTree.h"
      "${HEADER_DIR}/StructuredGenTree.h"
      "${HEADER_DIR}/TreeManager.h"
)

message("current source dir ${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE_LIST
      "HeaderTree.cxx"
      "FlatGenTree.cxx"
      "StructuredGenTree.cxx"
      "TreeManager.cxx"
)

add_library( GaranaAccessors SHARED ${SOURCE_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too 
target_include_directories(GaranaAccessors PUBLIC ../../include)

target_link_libraries(GaranaAccessors PUBLIC GaranaProducts GaranaBase ROOT::RIO ROOT::Tree ROOT::Physics)

# All users of this library will need at least C++11 
target_compile_features(GaranaAccessors PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
