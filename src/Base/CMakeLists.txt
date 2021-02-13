
# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_DIR "${PROJECT_SOURCE_DIR}/include/garana/Base")
set(HEADER_LIST 
      "${HEADER_DIR}/TreeReader.h"
      "${HEADER_DIR}/GenTree.h"
)
set(SOURCE_LIST
    "TreeReader.cxx"
    "GenTree.cxx"
)

add_library(GaranaBase SHARED ${SOURCE_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(GaranaBase PUBLIC ../../include)

# This depends on (header only)
target_link_libraries(GaranaBase PUBLIC ROOT::Tree ROOT::Core GaranaDict)

# All users of this library will need at least C++11
#target_compile_features(GaranaBase PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)

install(TARGETS GaranaBase DESTINATION lib)
install(FILES ${HEADER_LIST} DESTINATION include)

