cmake_minimum_required(VERSION 3.20)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}-test)

cmake_policy(SET CMP0076 NEW)
target_sources(
    ${PROJECT_NAME}-test
    PRIVATE
        test_result.cpp
        test_option.cpp
)

target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}-test PRIVATE GTest::GTest GTest::Main)

gtest_discover_tests(${PROJECT_NAME}-test)

# install output directory
install(
    TARGETS ${PROJECT_NAME}-test
    RUNTIME DESTINATION test
)