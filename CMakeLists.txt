cmake_minimum_required(VERSION 3.11)
project(search_engine VERSION 0.1)
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")
add_definitions( -DVERSION_CMAKE_PROJECT=${CMAKE_PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 20)

set(JSON_BuildTests OFF CACHE INTERNAL "")


set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(tests)

include(FetchContent)

include_directories(${CMAKE_SOURCE_DIR}/include)

FetchContent_Declare(json URL
        https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)

FetchContent_MakeAvailable(json)

add_executable(search_engine main.cpp
        include/converterJSON.h src/converterJSON.cpp
        include/invertedIndex.h src/invertedIndex.cpp
        include/searchServer.h src/searchServer.cpp
        )

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)



