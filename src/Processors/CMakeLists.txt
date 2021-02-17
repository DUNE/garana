
# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")

set(HEADER_DIR "${PROJECT_SOURCE_DIR}/include/garana/Processors")
set(HEADER_LIST 
      "${HEADER_DIR}/Mill.h"
      "${HEADER_DIR}/MillGenTree.h"
      "${HEADER_DIR}/MillHeaderTree.h"
)

message("current source dir ${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE_LIST
      "Mill.cxx"
      "MillGenTree.cxx"
      "MillHeaderTree.cxx"
)

add_library( GaranaProcessors SHARED ${SOURCE_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too 
target_include_directories(GaranaProcessors PUBLIC ../../include)

target_link_libraries(GaranaProcessors PUBLIC GaranaAccessors GaranaProducts GaranaBase ROOT::RIO ROOT::Tree ROOT::Physics GaranaDict)

# All users of this library will need at least C++11 
#target_compile_features(GaranaAccessors PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)

install(TARGETS GaranaProcessors DESTINATION lib)
install(FILES ${HEADER_LIST} DESTINATION include)
