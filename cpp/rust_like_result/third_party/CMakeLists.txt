
option(BUILD_GMOCK "Builds the googlemock subprojects" OFF)
option(INSTALL_GTEST "Enables installation of googletest" OFF)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(GTEST_CREATE_SHARED_LIBRARY ON CACHE BOOL "" FORCE)
set(CMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST CACHE STRING "" FORCE)
add_subdirectory(googletest)