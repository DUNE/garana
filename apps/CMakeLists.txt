
add_executable(gar gar.cxx)

target_include_directories(gar PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

target_link_libraries(gar PRIVATE
                        "${ROOT_LIBRARIES}"
                        #ROOT::Hist,
                        #ROOT::RIO,
                        #ROOT::Gpad,
                        GaranaAccessors
                        GaranaBase
                        GaranaProducts
                        GaranaDict
)

install(TARGETS gar DESTINATION bin)
