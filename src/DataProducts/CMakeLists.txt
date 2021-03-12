
set(LIBRARY_TARGET_NAME GaranaProducts)
set(DICTIONARY_TARGET_NAME GaranaDict)

set(HEADER_DIR "${PROJECT_SOURCE_DIR}/garana/DataProducts")

set(${LIBRARY_TARGET_NAME}_HDR
      "${HEADER_DIR}/GTruth.h"
      "${HEADER_DIR}/FSParticle.h"
      "${HEADER_DIR}/G4Particle.h"
      "${HEADER_DIR}/Track.h"
      "${HEADER_DIR}/Vertex.h"
      "${HEADER_DIR}/Vee.h"
      "${HEADER_DIR}/CaloCluster.h"
)
set(${DICTIONARY_TARGET_NAME}_HDR
      "${${LIBRARY_TARGET_NAME}_HDR}"
      "GaranaDict.h"
      "GaranaDictLinkDef.h"
)
set(${LIBRARY_TARGET_NAME}_SRC 
      "GTruth.cxx"
      "FSParticle.cxx"
      "G4Particle.cxx"
      "Track.cxx"
      "Vertex.cxx"
      "Vee.cxx"
      "CaloCluster.cxx"
)

# need to generate CINT dictionary so ROOT can understand whats in our trees
root_generate_dictionary(G__GaranaDict ${CMAKE_CURRENT_SOURCE_DIR}/GaranaDict.h LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/GaranaDictLinkDef.h)
add_library(${DICTIONARY_TARGET_NAME} ${${LIBRARY_TARGET_NAME}_SRC} ${${LIBRARY_TARGET_NAME}_HDR} G__GaranaDict.cxx)

set_target_properties(${DICTIONARY_TARGET_NAME} PROPERTIES VERSION       ${${PROJECT_NAME}_VERSION}
                                                        PUBLIC_HEADER "${${LIBRARY_TARGET_NAME}_HDR}")

target_link_libraries(${DICTIONARY_TARGET_NAME} PUBLIC ROOT::Core)

add_library( ${LIBRARY_TARGET_NAME} ${${LIBRARY_TARGET_NAME}_SRC} ${${LIBRARY_TARGET_NAME}_HDR})

# We need this directory, and users of our library will need it too
set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES VERSION       ${${PROJECT_NAME}_VERSION}
                                                        PUBLIC_HEADER "${${LIBRARY_TARGET_NAME}_HDR}")

# We need this directory, and users of our library will need it too 
target_include_directories(${LIBRARY_TARGET_NAME} PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
)

# This depends on (header only)
target_link_libraries(${LIBRARY_TARGET_NAME} PUBLIC ROOT::Physics ${DICTIONARY_TARGET_NAME})

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/garana"
  PREFIX "Header Files"
  FILES ${${LIBRARY_TARGET_NAME}_HDR}
)

#move some products from dictionary generation to lib dir in build area
install(FILES 
          "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libGaranaDict_rdict.pcm"
          "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libGaranaDict.rootmap"
          DESTINATION lib
)

message(STATUS "installed files libGaranaDict_rdict.pcm and libGaranaDict.rootmap. move on to installing targets")

install(TARGETS ${DICTIONARY_TARGET_NAME} ${LIBRARY_TARGET_NAME}
        EXPORT  ${PROJECT_NAME}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_TARGET_NAME}" COMPONENT dev
)
        
message(STATUS "Created target ${LIBRARY_TARGET_NAME} for export ${PROJECT_NAME}.")
