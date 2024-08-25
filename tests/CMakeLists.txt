cmake_minimum_required(VERSION 3.27)
project(tests)

include(GoogleTest)

include(../cmake_scripts/set_default_properties.cmake)

set_default_properties()

enable_testing()

find_package(GTest CONFIG REQUIRED)

set(DynamicObject_DIR ../lib/cmake/DynamicObject)
find_package(DynamicObject CONFIG REQUIRED)

add_executable(tests castsTests.cpp)

target_link_libraries(tests PRIVATE DynObj::DynamicObject GTest::gtest)
target_include_directories(tests PRIVATE ${DynamicObject_INCLUDE_DIRS})

gtest_discover_tests(tests)
