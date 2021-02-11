cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(garana VERSION 1.0.0 DESCRIPTION "analysis tools for garsoft analysis")

find_package(ROOT 6.16 CONFIG REQUIRED)

add_subdirectory(garana)

install(TARGETS garanaaccessors garanabase garanaproducts
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(gar gar.cxx)
target_link_libraries(gar PUBLIC garanaaccessors ROOT::Hist ROOT::RIO ROOT::Gpad)                       #StructuredGenTree FlatGenTree)
