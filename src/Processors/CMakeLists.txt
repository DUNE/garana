
IF(BUILD_W_CET)

    art_make(BASENAME_ONLY
         LIBRARY_NAME GaranaProcessors
         LIB_LIBRARIES #src_DataProducts
                       GaranaProducts
                       GaranaBase
                       GaranaAccessors
                       ${ROOT_BASIC_LIB_LIST}
        )

    install_headers()
    install_source()

ELSE()

    set(LIBRARY_TARGET_NAME GaranaProcessors)
    
    set(HEADER_DIR "${PROJECT_SOURCE_DIR}/garana/Processors")
    set($LIBRARY_TARGET_NAME}_HD
          "${HEADER_DIR}/Mill.h"
          "${HEADER_DIR}/MillGenTree.h"
          "${HEADER_DIR}/MillHeaderTree.h"
    )
    
    message("current source dir ${CMAKE_CURRENT_SOURCE_DIR}")
    set(${LIBRARY_TARGET_NAME}_SRC
          "Mill.cxx"
          "MillGenTree.cxx"
          "MillHeaderTree.cxx"
    )
    
    add_library( ${LIBRARY_TARGET_NAME} SHARED ${${LIBRARY_TARGET_NAME}_SRC} ${${LIBRARY_TARGET_NAME}_HDR})
    target_link_libraries(${LIBRARY_TARGET_NAME} PUBLIC GaranaAccessors GaranaProducts GaranaBase ROOT::RIO ROOT::Tree ROOT::Physics GaranaDict)
    
    # IDEs should put the headers in a nice place
    source_group(
      TREE "${PROJECT_SOURCE_DIR}/garana"
      PREFIX "Header Files"
      FILES ${${LIBRARY_TARGET_NAME}_HDR} #${HEADER_LIST}
    )
    
    install(TARGETS ${LIBRARY_TARGET_NAME}
            EXPORT  ${PROJECT_NAME}
            LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
            ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
            RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
            PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_TARGET_NAME}" COMPONENT deV
    )
    
    message(STATUS "Created target ${LIBRARY_TARGET_NAME} for export ${PROJECT_NAME}.")

ENDIF()
