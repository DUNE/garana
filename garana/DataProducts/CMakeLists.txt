IF( BUILD_W_CET )

  cet_make( LIBRARY_NAME GaranaProducts
            LIBRARIES ${ROOT_BASIC_LIB_LIST}
            NO_DICTIONARY 
  )

  build_dictionary(GaranaDict DICTIONARY_LIBRARIES GaranaProducts)


  install_headers()
  install_source()

ELSE()

    set(LIBRARY_TARGET_NAME GaranaProducts)
    #set(DICTIONARY_TARGET_NAME GaranaDict)
    
    #set(HEADER_DIR "${PROJECT_SOURCE_DIR}/garana/DataProducts")
    
    set(${LIBRARY_TARGET_NAME}_HDR
          #"${HEADER_DIR}/GTruth.h"
          #"${HEADER_DIR}/FSParticle.h"
          #"${HEADER_DIR}/G4Particle.h"
          #"${HEADER_DIR}/Track.h"
          #"${HEADER_DIR}/Vertex.h"
          #"${HEADER_DIR}/Vee.h"
          #"${HEADER_DIR}/CaloCluster.h"
          "GTruth.h"
          "FSParticle.h"
          "G4Particle.h"
          "Track.h"
          "Vertex.h"
          "Vee.h"
          "CaloCluster.h"
          
    )
    set(${DICTIONARY_TARGET_NAME}_HDR
          "${${LIBRARY_TARGET_NAME}_HDR}"
          "classes.h"
          #"GaranaDictLinkDef.h"
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
    
    #message(STATUS "generating ROOT dictionary...")
    # need to generate CINT dictionary so ROOT can understand whats in our trees
    #root_generate_dictionary(G__GaranaDict ${CMAKE_CURRENT_SOURCE_DIR}/GaranaDict.h LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/GaranaDictLinkDef.h)
    REFLEX_GENERATE_DICTIONARY(G__${DICTIONARY_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/classes.h 
                               SELECTION ${CMAKE_CURRENT_SOURCE_DIR}/classes_def.xml)

    #message(STATUS "done.")
    add_library(${DICTIONARY_TARGET_NAME} SHARED ${${DICTIONARY_TARGET_NAME}_HDR} G__${DICTIONARY_TARGET_NAME}.cxx)
    
    set_target_properties(${DICTIONARY_TARGET_NAME} PROPERTIES VERSION       ${${PROJECT_NAME}_VERSION}
                                                            PUBLIC_HEADER "${${DICTIONARY_TARGET_NAME}_HDR}")
    
    target_link_libraries(${DICTIONARY_TARGET_NAME} PUBLIC ROOT::Core ROOT::Physics)
    
    add_library( ${LIBRARY_TARGET_NAME} ${${LIBRARY_TARGET_NAME}_SRC} ${${LIBRARY_TARGET_NAME}_HDR})
    
    # We need this directory, and users of our library will need it too
    set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES VERSION       ${${PROJECT_NAME}_VERSION}
                                                            PUBLIC_HEADER "${${LIBRARY_TARGET_NAME}_HDR}")
    #target_link_libraries(${LIBRARY_TARGET_NAME} PUBLIC ROOT::Core ROOT::Physics ${DICTIONARY_TARGET_NAME})    

    # We need this directory, and users of our library will need it too 
    target_include_directories(${LIBRARY_TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
    )
    
    # This depends on (header only)
    #target_link_libraries(${DICTIONARY_TARGET_NAME} PUBLIC ROOT::Physics ${LIBRARY_TARGET_NAME}  )
    
    # IDEs should put the headers in a nice place
    source_group(
      TREE "${PROJECT_SOURCE_DIR}/garana"
      PREFIX "Header Files"
      FILES ${${LIBRARY_TARGET_NAME}_HDR}
    )
    
    #move some products from dictionary generation to lib dir in build area
    install(FILES 
              #"${CMAKE_INSTALL_LIBDIR}/G__${DICTIONARY_TARGET_NAME}_rdict.pcm"
              #"${CMAKE_INSTALL_LIBDIR}/G__${DICTIONARY_TARGET_NAME}Dict.rootmap"
              #"${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib${DICTIONARY_TARGET_NAME}_rdict.pcm" # use with root_generate_dictionary
              #"${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib${DICTIONARY_TARGET_NAME}.rootmap"   # use with root_generate_dictionary  
              "${CMAKE_BINARY_DIR}/garana/DataProducts/G__${DICTIONARY_TARGET_NAME}_rdict.pcm"
              "${CMAKE_BINARY_DIR}/garana/DataProducts/G__${DICTIONARY_TARGET_NAME}Dict.rootmap"
              DESTINATION lib
    )
    
    message(STATUS "attempting to install files G__GaranaDict_rdict.pcm and G__GaranaDictDict.rootmap 
                      in directory, ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    
    message(STATUS "Cmake install libdir:  ${CMAKE_INSTALL_LIBDIR}")
    message(STATUS "Cmake install bindir:  ${CMAKE_INSTALL_BINDIR}")
    message(STATUS "Cmake install include dir: ${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_TARGET_NAME}")  
    message(STATUS "Cmake install src dir: ${CMAKE_INSTALL_SRCDIR}")  
    install(TARGETS  ${DICTIONARY_TARGET_NAME} ${LIBRARY_TARGET_NAME}
            EXPORT  ${PROJECT_NAME}
            LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
            ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
            RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
            PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_TARGET_NAME}" COMPONENT dev
    )
            
    message(STATUS "Created target ${LIBRARY_TARGET_NAME} for export ${PROJECT_NAME}.")

ENDIF()
