
add_library( GaranaBase SHARED
             ${CMAKE_CURRENT_SOURCE_DIR}/TreeReader.cxx
             ${CMAKE_CURRENT_SOURCE_DIR}/GenTree.cxx
           )

set_target_properties( GaranaBase PROPERTIES PUBLIC_HEADER
                       "TreeReader.h;
                        GenTree.h"
                     )


target_include_directories(GaranaBase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GaranaBase PUBLIC ROOT::Tree)

#install(TARGETS garanabase LIBRARY DESTINATION lib)
#install (FILES *.h PUBLIC_HEADER DESTINATION include)

