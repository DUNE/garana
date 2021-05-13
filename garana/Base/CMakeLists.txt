
IF(BUILD_W_CET)

    art_make(BASENAME_ONLY
         LIBRARY_NAME GaranaBase
         LIB_LIBRARIES #src_DataProducts
                       GaranaProducts
                       ${ROOT_BASIC_LIB_LIST}
        )

    install_headers()
    install_source()

ELSE()

    set(LIBRARY_TARGET_NAME GaranaBase)
    
    set(HEADER_DIR "${PROJECT_SOURCE_DIR}/garana/Base")
    set(${LIBRARY_TARGET_NAME}_HDR 
          "${HEADER_DIR}/TreeReader.h"
          "${HEADER_DIR}/GenTree.h"
          "${HEADER_DIR}/G4Tree.h"
          "${HEADER_DIR}/DetTree.h"
          "${HEADER_DIR}/RecoTree.h"
          "${HEADER_DIR}/DisplayTree.h"
    )
    set(${LIBRARY_TARGET_NAME}_SRC
        "TreeReader.cxx"
        "GenTree.cxx"
        "G4Tree.cxx"
        "DetTree.cxx"
        "RecoTree.cxx"
        "DisplayTree.cxx"
    )
    
    add_library(${LIBRARY_TARGET_NAME} SHARED ${${LIBRARY_TARGET_NAME}_SRC} ${${LIBRARY_TARGET_NAME}_HDR})
    
    set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES VERSION       ${${PROJECT_NAME}_VERSION}
                                                            PUBLIC_HEADER "${${LIBRARY_TARGET_NAME}_HDR}")
    
    # We need this directory, and users of our library will need it too
    #target_include_directories(${LIBRARY_TARGET_NAME} PUBLIC ../../include)
    target_include_directories(${LIBRARY_TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
    )
    
    # This depends on (header only)
    target_link_libraries(${LIBRARY_TARGET_NAME} PUBLIC ROOT::Tree ROOT::Core GaranaDict)
    
    # IDEs should put the headers in a nice place
    source_group(
      TREE "${PROJECT_SOURCE_DIR}/garana"
      PREFIX "Header Files"
      FILES ${${LIBRARY_TARGET_NAME}_HDR} #${HEADER_LIST}
    )
    
    #install(TARGETS GaranaBase DESTINATION lib)
    #install(FILES ${HEADER_LIST} DESTINATION include)
    
    install(TARGETS ${LIBRARY_TARGET_NAME}
            EXPORT  ${PROJECT_NAME}
            LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
            ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
            RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
            PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_TARGET_NAME}" COMPONENT deV
    )
    
    message(STATUS "Created target ${LIBRARY_TARGET_NAME} for export ${PROJECT_NAME}.")

ENDIF()
