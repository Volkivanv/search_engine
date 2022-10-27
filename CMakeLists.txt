cmake_minimum_required(VERSION 3.23)
project(search_engine VERSION 0.1)
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")
add_definitions( -DVERSION_CMAKE_PROJECT=${CMAKE_PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)


set(JSON_BuildTests OFF CACHE INTERNAL "")


add_subdirectory(nlohmann_json)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

