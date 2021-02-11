add_library(HeaderTree HeaderTree.cxx)
add_library(FlatGenTree FlatGenTree.cxx)
add_library(StructuredGenTree StructuredGenTree.cxx)
add_library(TreeManager TreeManager.cxx)

target_include_directories(HeaderTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 
target_include_directories(FlatGenTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(StructuredGenTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(TreeManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HeaderTree PUBLIC TreeReader)
target_link_libraries(FlatGenTree PUBLIC GenTree)
target_link_libraries(StructuredGenTree PUBLIC GenTree FSParticle GTruth ROOT::Physics)
target_link_libraries(TreeManager PUBLIC HeaderTree FlatGenTree StructuredGenTree ROOT::RIO)
