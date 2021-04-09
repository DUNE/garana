
 IF(BUILD_W_CET)

    art_make_exec( NAME gar
                   SOURCE gar.cxx
                   LIBRARIES GaranaUtility
                             GaranaAccessors
                             GaranaBase
                             GaranaProducts )
                   #NO_INSTALL)

    art_make_exec( NAME paulbunyan
                   SOURCE paulbunyan.cxx
                   LIBRARIES GaranaUtility
                             GaranaAccessors
                             GaranaProcessors
                             GaranaBase
                             GaranaProducts )
                   #NO_INSTALL)

    art_make_exec( NAME test_derived_flat_tree
                   SOURCE test_derived_flat_tree.cxx
                   LIBRARIES GaranaUtility
                             GaranaAccessors
                             GaranaProcessors
                             GaranaBase
                             GaranaProducts )
                   #NO_INSTALL)

    install_scripts()

 ELSE()
    #### setup for gar ####
    add_executable(gar gar.cxx)
    
    target_include_directories(gar PUBLIC
                               "${PROJECT_BINARY_DIR}"
                               )
    
    target_link_libraries(gar# PRIVATE
                            "${ROOT_LIBRARIES}"
                            #ROOT::Hist,
                            #ROOT::RIO,
                            #ROOT::Gpad,
                            GaranaUtility
                            GaranaAccessors
                            GaranaBase
                            #src_DataProducts
                            GaranaProducts
                            #GaranaDict
    
    )
    
    #### setup for paulbunyan ####
    add_executable(paulbunyan paulbunyan.cxx)
    
    target_include_directories(paulbunyan PUBLIC
                               "${PROJECT_BINARY_DIR}"
                               )
    
    target_link_libraries(paulbunyan# PRIVATE
                            "${ROOT_LIBRARIES}"
                            #ROOT::Hist,
                            #ROOT::RIO,
                            #ROOT::Gpad,
                            GaranaAccessors
                            GaranaBase
                            #src_DataProducts
                            GaranaProducts
                            #GaranaDict
                            GaranaProcessors
    
    )
    
    #### setup for test_derived_flat_tree ####
    add_executable(test_derived_flat_tree test_derived_flat_tree.cxx)
    
    target_include_directories(test_derived_flat_tree PUBLIC
                               "${PROJECT_BINARY_DIR}"
                              )
    
    target_link_libraries(test_derived_flat_tree# PRIVATE
                            "${ROOT_LIBRARIES}"
                            #ROOT::Hist,
                            #ROOT::RIO,
                            #ROOT::Gpad,
                            GaranaAccessors
                            GaranaBase
                            #src_DataProducts
                            GaranaProducts
                            #GaranaDict
                            GaranaProcessors
    )
    
    #### set install paths #####
    install(TARGETS gar paulbunyan test_derived_flat_tree DESTINATION bin)
    
 ENDIF()
