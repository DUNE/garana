
set(LIBRARY_TARGET_NAME GaranaUtility)

set(HEADER_DIR "${PROJECT_SOURCE_DIR}/garana/Utility")
set($LIBRARY_TARGET_NAME}_HDR
      "${HEADER_DIR}/Backtracker.h"
)

message("current source dir ${CMAKE_CURRENT_SOURCE_DIR}")
set(${LIBRARY_TARGET_NAME}_SRC
      "Backtracker.cxx"
)

add_library( ${LIBRARY_TARGET_NAME} SHARED ${${LIBRARY_TARGET_NAME}_SRC} ${${LIBRARY_TARGET_NAME}_HDR})
add_library(${PROJECT_NAME}::${LIBRARY_TARGET_NAME} ALIAS ${LIBRARY_TARGET_NAME})

set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES VERSION       ${${PROJECT_NAME}_VERSION}
                                                        PUBLIC_HEADER "${${LIBRARY_TARGET_NAME}_HDR}")

# We need this directory, and users of our library will need it too 
target_include_directories(${LIBRARY_TARGET_NAME} PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${LIBRARY_TARGET_NAME} PUBLIC GaranaAccessors GaranaProducts GaranaBase ROOT::Tree GaranaDict)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/garana"
  PREFIX "Header Files"
  FILES ${${LIBRARY_TARGET_NAME}_HDR}
)

install(TARGETS ${LIBRARY_TARGET_NAME}
        EXPORT  ${PROJECT_NAME}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_TARGET_NAME}" COMPONENT deV
)

message(STATUS "Created target ${LIBRARY_TARGET_NAME} for export ${PROJECT_NAME}.")