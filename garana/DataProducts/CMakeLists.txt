add_library(FSParticle FSParticle.cxx)
add_library(GTruth GTruth.cxx)

target_include_directories(FSParticle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(GTruth PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(FSParticle PUBLIC ROOT::Physics)
target_link_libraries(GTruth PUBLIC ROOT::Physics)
