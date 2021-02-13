
# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_DIR "${PROJECT_SOURCE_DIR}/include/garana/DataProducts")
message("DataProducts header dir: ${HEADER_DIR}")
set(HEADER_LIST 
      "${HEADER_DIR}/GTruth.h"
      "${HEADER_DIR}/FSParticle.h"
)
set(SOURCE_LIST 
      "GTruth.cxx"
      "FSParticle.cxx"
)

add_library(GaranaProducts SHARED ${SOURCE_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(GaranaProducts PUBLIC "../../include")

root_generate_dictionary(G__GaranaDict GaranaDict.h LINKDEF GaranaDictLinkDef.h)
add_library(GaranaDict SHARED ${SOURCE_LIST} ${HEADER_LIST} G__GaranaDict.cxx)
target_include_directories(GaranaDict  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(GaranaDict PUBLIC ROOT::Core)

# This depends on (header only)
target_link_libraries(GaranaProducts PUBLIC ROOT::Physics GaranaDict)

#target_link_libraries(GaranaDict PUBLIC GaranaProducts ROOT::Core)

# All users of this library will need at least C++11
#target_compile_features(GaranaProducts PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)

install(TARGETS GaranaProducts GaranaDict DESTINATION lib)
install(FILES ${HEADER_LIST} DESTINATION include)
install(FILES "${CMAKE_BINARY_DIR}/garana/src/DataProducts/libGaranaDict_rdict.pcm" DESTINATION lib)
