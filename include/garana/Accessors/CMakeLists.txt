add_library( GaranaAccessors SHARED
             ${CMAKE_CURRENT_SOURCE_DIR}/HeaderTree.cxx
             ${CMAKE_CURRENT_SOURCE_DIR}/FlatGenTree.cxx
             ${CMAKE_CURRENT_SOURCE_DIR}/StructuredGenTree.cxx
             ${CMAKE_CURRENT_SOURCE_DIR}/TreeManager.cxx
           )

set_target_properties( GaranaAccessors PROPERTIES PUBLIC_HEADER
                       "${CMAKE_CURRENT_SOURCE_DIR}/HeaderTree.h;
                        ${CMAKE_CURRENT_SOURCE_DIR}/FlatGenTree.h;
                        ${CMAKE_CURRENT_SOURCE_DIR}/StructuredGenTree.h;
                        ${CMAKE_CURRENT_SOURCE_DIR}/TreeManager.h"
                     )


target_include_directories(GaranaAccessors PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GaranaAccessors PUBLIC GaranaProducts GaranaBase ROOT::RIO)

#install(TARGETS GaranaAccessors LIBRARY DESTINATION lib)
#install (FILES *.h PUBLIC_HEADER DESTINATION include)
