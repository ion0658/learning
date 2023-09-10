cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}-example)
cmake_policy(SET CMP0079 NEW)
target_sources(
    ${PROJECT_NAME}-example
    PRIVATE
        main.cpp
)

target_link_libraries(${PROJECT_NAME}-example PRIVATE ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}-example PRIVATE Threads::Threads)

# if need set rpath
# SET_TARGET_PROPERTIES(
#     ${example_name}
#     PROPERTIES INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/"
# )

# install output directory
install(
    TARGETS ${PROJECT_NAME}-example
    RUNTIME DESTINATION bin
)

install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    # コピー先
    DESTINATION examples
)