cmake_minimum_required (VERSION 3.11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SrcFiles
        ${MY_SRC_DIR}/invertedIndex.cpp
        ${MY_SRC_DIR}/searchServer.cpp
        ${MY_SRC_DIR}/converterJSON.cpp
        )
set(HeadFiles
        ${MY_INCLUDE_DIR}/converterJSON.h
        ${MY_INCLUDE_DIR}/searchServer.h
        ${MY_INCLUDE_DIR}/invertedIndex.h
        )

include_directories(../include ../src )
include_directories(../nlohmann_json)

set(TestsFiles searchEngine_tests.cpp)

add_executable(GtestTests ${TestsFiles} ${SrcFiles} ${HeadFiles})

include(GoogleTest)

target_link_libraries(GtestTests PRIVATE nlohmann_json::nlohmann_json gtest gtest_main )

gtest_discover_tests(GtestTests)