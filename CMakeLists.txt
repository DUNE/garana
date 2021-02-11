cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(garana)

find_package(ROOT 6.16 CONFIG REQUIRED)

add_subdirectory(garana)

add_executable(gar gar.cxx)
target_link_libraries(gar PUBLIC TreeManager ROOT::Hist ROOT::RIO ROOT::Gpad 
                      StructuredGenTree FlatGenTree)
