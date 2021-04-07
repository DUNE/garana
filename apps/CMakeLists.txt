
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
                        src_DataProducts
                        #GaranaProducts
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
                        src_DataProducts
                        #GaranaProducts
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
                        src_DataProducts
                        #GaranaProducts
                        #GaranaDict
                        GaranaProcessors
)

#### set install paths #####
install(TARGETS gar paulbunyan test_derived_flat_tree DESTINATION bin)
