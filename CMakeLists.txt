cmake_minimum_required(VERSION 3.23)
project(search_engine)

set(CMAKE_CXX_STANDARD 20)
#set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
#add_executable(search_engine src/main.cpp src/converterJSON.cpp ${MY_INCLUDE_DIR}/converterJSON.h)
add_subdirectory(src)

#include(FetchContent)
#FetchContent_Declare(
 #       googletest
 #       URL
 #       https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#)

#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#set(gtest_disable_pthreads on)

#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)

#enable_testing()

#target_link_libraries(search_engine PRIVATE gtest_main)
#include(GoogleTest)
#gtest_discover_tests(search_engine)








set(JSON_BuildTests OFF CACHE INTERNAL "")

# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.

# If you only include this third party in PRIVATE source files, you do not
# need to install it when your main project gets installed.
# set(JSON_Install OFF CACHE INTERNAL "")

# Don't use include(nlohmann_json/CMakeLists.txt) since that carries with it
# unintended consequences that will break the build.  It's generally
# discouraged (although not necessarily well documented as such) to use
# include(...) for pulling in other CMake projects anyways.
add_subdirectory(nlohmann_json)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

