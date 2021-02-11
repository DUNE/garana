add_library(TreeReader TreeReader.cxx)
add_library(GenTree GenTree.cxx)

target_include_directories(TreeReader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(GenTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(TreeReader PUBLIC ROOT::Tree)
target_link_libraries(GenTree PUBLIC TreeReader)
