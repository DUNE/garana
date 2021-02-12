add_executable(gar gar.cxx)
target_compile_features(gar PRIVATE cxx_std_17)

target_link_libraries(gar PUBLIC 
                        GaranaAccessors
                        ROOT::Hist
                        ROOT::RIO
                        ROOT::Gpad
)

