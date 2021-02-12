
add_library( GaranaProducts SHARED
             ${CMAKE_CURRENT_SOURCE_DIR}/GTruth.cxx
             ${CMAKE_CURRENT_SOURCE_DIR}/FSParticle.cxx
           )

set_target_properties( GaranaProducts PROPERTIES PUBLIC_HEADER
                       "GTruth.h;
                        FSParticle.h"
                     )


target_include_directories(GaranaProducts PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GaranaProducts PUBLIC ROOT::Physics)

#install(TARGETS garanaproducts LIBRARY DESTINATION lib)
#install (FILES *.h PUBLIC_HEADER DESTINATION include)

