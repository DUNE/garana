add_subdirectory(Accessors)
add_subdirectory(Base)
add_subdirectory(DataProducts)

#add_library( garanaaccessors SHARED
#             Accessors/HeaderTree.cxx
#             Accessors/FlatGenTree.cxx
#             Accessors/StructuredGenTree.cxx
#             Accessors/TreeManager.cxx
#           )

#add_library( garanabase SHARED
#             Base/TreeReader.cxx
#             Base/GenTree.cxx
#           )

#add_library( garanaproducts SHARED
#             DataProducts/GTruth.cxx
#             DataProducts/FSParticle.cxx
#           )

#set_target_properties(garanaaccessors PROPERTIES VERSION ${PROJECT_VERSION})
#set_target_properties(garanabase PROPERTIES VERSION ${PROJECT_VERSION})
#set_target_properties(garanaproducts PROPERTIES VERSION ${PROJECT_VERSION})

#target_include_directories(garanaaccessors PUBLIC ./Accessors)
#target_include_directories(garanabase PUBLIC ./Base)
#target_include_directories(garanaproducts PUBLIC ./DataProducts)


#install(TARGETS garanaaccessors garanabase garanaproducts
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
