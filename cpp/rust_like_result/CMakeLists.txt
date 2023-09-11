# CMakeLists.txt

# required cmake version
cmake_minimum_required(VERSION 3.20)
# project name
project(ion_oh_result_option VERSION 0.1 LANGUAGES CXX)

# set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

# Almost project use Thread
find_package(Threads REQUIRED)

# Build shared libraries by default
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." True)

# enable testing by default
option(BUILD_TESTING "" ON)

# enable examples by default
option(BUILD_EXAMPLES "" ON)

# Force -Wall/-Wextra on gcc and clang (and /W4 for MSVC)
if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-long-long -pedantic")
endif()

# set rpath on macOS
if (APPLE)
  set(CMAKE_MACOSX_RPATH 1)
endif(APPLE)

# set library type
if (BUILD_SHARED_LIBS)
    set (LIB_TYPE SHARED)
else ()   
    set (LIB_TYPE STATIC)
endif (BUILD_SHARED_LIBS)
# header only
add_library(${PROJECT_NAME} INTERFACE)

## installing settings

target_include_directories(
    ${PROJECT_NAME} INTERFACE
    # 通常のビルドで使われるインクルードパス
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    # インストールされたパッケージを利用するとき使われるインクルードパス
    $<INSTALL_INTERFACE:include>
)

install(
    TARGETS ${PROJECT_NAME} 
    # 生成するconfigファイルの名前
    EXPORT ${PROJECT_NAME}-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    EXPORT ${PROJECT_NAME}-config
    # 名前空間の指定
    NAMESPACE ${PROJECT_NAME}::
    # インストール先
    DESTINATION lib/cmake/${PROJECT_NAME}
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    # コピー先
    DESTINATION include
)

# alias
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

include(CMakePackageConfigHelpers)

# Package Version Fileの生成
write_basic_package_version_file(
    # 生成するファイルの名前
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    # 互換性の判定方法の指定
    COMPATIBILITY SameMajorVersion
)

# Package Version Fileのインストール
install(
    # コピー元
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    # コピー先
    DESTINATION lib/cmake/${PROJECT_NAME}
)

if (BUILD_EXAMPLES)
    # application directory
    add_subdirectory(${PROJECT_SOURCE_DIR}/examples)
endif()

# if testing is enabled, add test directory
if(BUILD_TESTING)    
    enable_testing()
    add_subdirectory(${PROJECT_SOURCE_DIR}/third_party)
    add_subdirectory(${PROJECT_SOURCE_DIR}/test)
endif()

