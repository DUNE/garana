
IF(BUILD_W_CET)

    art_make(BASENAME_ONLY
         LIBRARY_NAME GaranaAccessors
         LIB_LIBRARIES #src_DataProducts
                       GaranaProducts
                       GaranaBase
                       ${ROOT_BASIC_LIB_LIST}
        )

    install_headers()
    install_source()

ELSE()

    set(LIBRARY_TARGET_NAME GaranaAccessors)
    set(HEADER_DIR "${PROJECT_SOURCE_DIR}/garana/Accessors")
    set(${LIBRARY_TARGET_NAME}_HDR 
          "${HEADER_DIR}/HeaderTree.h"
          "${HEADER_DIR}/FlatGenTree.h"
          "${HEADER_DIR}/FlatG4Tree.h"
          "${HEADER_DIR}/FlatDetTree.h"
          "${HEADER_DIR}/FlatRecoTree.h"
          "${HEADER_DIR}/FlatDisplayTree.h"
          "${HEADER_DIR}/StructuredGenTree.h"
          "${HEADER_DIR}/StructuredG4Tree.h"
          "${HEADER_DIR}/StructuredDetTree.h"
          "${HEADER_DIR}/StructuredRecoTree.h"
          "${HEADER_DIR}/StructuredDisplayTree.h"
          "${HEADER_DIR}/TreeManager.h"
    )
    
    set(${LIBRARY_TARGET_NAME}_SRC
          "HeaderTree.cxx"
          "FlatGenTree.cxx"
          "FlatG4Tree.cxx"
          "FlatDetTree.cxx"
          "FlatRecoTree.cxx"
          "FlatDisplayTree.cxx"
          "StructuredGenTree.cxx"
          "StructuredG4Tree.cxx"
          "StructuredDetTree.cxx"
          "StructuredRecoTree.cxx"
          "StructuredDisplayTree.cxx"
          "TreeManager.cxx"
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
    
    target_link_libraries(${LIBRARY_TARGET_NAME} PUBLIC GaranaProducts GaranaBase ROOT::RIO ROOT::Tree ROOT::Physics ROOT::Core GaranaDict)
    
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
    

ENDIF()
