cmake_minimum_required(VERSION 3.20)
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)

message(STATUS "gtest_SOURCE_DIR = ${gtest_SOURCE_DIR}")
message(STATUS "gmock_SOURCE_DIR = ${gmock_SOURCE_DIR}")

add_executable(${PROJECT_NAME}-test)

cmake_policy(SET CMP0076 NEW)
target_sources(
    ${PROJECT_NAME}-test
    PRIVATE
        test_result.cpp
        test_option.cpp
)

include(GoogleTest)

target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}-test
    PRIVATE
        ${gtest_SOURCE_DIR}/include
)
#target_include_directories(${PROJECT_NAME}-test PRIVATE ${PROJECT_SOURCE_DIR}/third_party/googletest/googletest/include)
target_link_libraries(${PROJECT_NAME}-test PRIVATE gtest gtest_main)

gtest_discover_tests(
    ${PROJECT_NAME}-test
#   CMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST
)

# install output directory
install(
    TARGETS ${PROJECT_NAME}-test
    RUNTIME DESTINATION test
)