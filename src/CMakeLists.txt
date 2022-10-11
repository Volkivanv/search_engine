cmake_minimum_required(VERSION 3.23)
set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
add_executable(search_engine main.cpp converterJSON.cpp invertedIndex.cpp searchEngineTest.cpp
        ${MY_INCLUDE_DIR}/converterJSON.h ${MY_INCLUDE_DIR}/invertedIndex.h )
#Testing system
include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(search_engine PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(search_engine)

#src files



TARGET_INCLUDE_DIRECTORIES(search_engine PUBLIC ${MY_INCLUDE_DIR})