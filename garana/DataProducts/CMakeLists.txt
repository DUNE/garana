#add_library(FSParticle FSParticle.cxx)
#add_library(GTruth GTruth.cxx)

add_library( garanaproducts SHARED
             ${CMAKE_CURRENT_SOURCE_DIR}/GTruth.cxx
             ${CMAKE_CURRENT_SOURCE_DIR}/FSParticle.cxx
           )

#target_include_directories(FSParticle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(GTruth PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(garanaproducts PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#target_link_libraries(FSParticle PUBLIC ROOT::Physics)
#target_link_libraries(GTruth PUBLIC ROOT::Physics)
target_link_libraries(garanaproducts PUBLIC ROOT::Physics)

#target_include_directories(garanaproducts PRIVATE .)
