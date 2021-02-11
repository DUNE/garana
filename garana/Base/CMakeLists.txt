#add_library(TreeReader TreeReader.cxx)
#add_library(GenTree GenTree.cxx)

add_library( garanabase SHARED
             ${CMAKE_CURRENT_SOURCE_DIR}/TreeReader.cxx
             ${CMAKE_CURRENT_SOURCE_DIR}/GenTree.cxx
           )

#target_include_directories(TreeReader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(GenTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(garanabase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


#target_link_libraries(TreeReader PUBLIC ROOT::Tree)
#target_link_libraries(GenTree PUBLIC TreeReader)
target_link_libraries(garanabase PUBLIC ROOT::Tree)

#target_include_directories(garanabase PRIVATE .)
