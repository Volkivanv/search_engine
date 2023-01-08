cmake_minimum_required (VERSION 3.11)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)



enable_testing()
FetchContent_MakeAvailable(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SrcFiles
        ${MY_SRC_DIR}/invertedIndex.cpp
        ${MY_SRC_DIR}/searchServer.cpp

        )
set(HeadFiles

        ${MY_INCLUDE_DIR}/searchServer.h
        ${MY_INCLUDE_DIR}/invertedIndex.h
        )

include_directories(../include ../src )


set(TestsFiles searchEngine_tests.cpp)

add_executable(GtestTests ${TestsFiles} ${SrcFiles} ${HeadFiles})

include(GoogleTest)

target_link_libraries(GtestTests PRIVATE gtest gtest_main )

gtest_discover_tests(GtestTests)