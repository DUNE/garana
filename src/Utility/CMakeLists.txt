
set(LIBRARY_TARGET_NAME GaranaUtility)

set(HEADER_DIR "${PROJECT_SOURCE_DIR}/garana/Utility")
set($LIBRARY_TARGET_NAME}_HD
      "${HEADER_DIR}/Backtracker.h"
)

message("current source dir ${CMAKE_CURRENT_SOURCE_DIR}")
set(${LIBRARY_TARGET_NAME}_SRC
      "Backtracker.cxx"
)

add_library( ${LIBRARY_TARGET_NAME} SHARED ${${LIBRARY_TARGET_NAME}_SRC} ${${LIBRARY_TARGET_NAME}_HDR})

# We need this directory, and users of our library will need it too 
#target_include_directories(GaranaUtility PUBLIC ../../include)

target_link_libraries(${LIBRARY_TARGET_NAME} PUBLIC GaranaAccessors GaranaProducts GaranaBase ROOT::Tree GaranaDict)

# All users of this library will need at least C++11 
#target_compile_features(GaranaAccessors PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/garana"
  PREFIX "Header Files"
  FILES ${${LIBRARY_TARGET_NAME}_HDR} #${HEADER_LIST}
)

#install(TARGETS GaranaUtility DESTINATION lib)
#install(FILES ${HEADER_LIST} DESTINATION include)

install(TARGETS ${LIBRARY_TARGET_NAME}
        EXPORT  ${PROJECT_NAME}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_TARGET_NAME}" COMPONENT deV
)

message(STATUS "Created target ${LIBRARY_TARGET_NAME} for export ${PROJECT_NAME}.")