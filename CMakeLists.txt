cmake_minimum_required(VERSION 3.28)
project(bad_apple_ascii)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置可执行文件/DLL输出目录 (Windows DLL 会输出到这里)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# 设置静态库(.a/.lib)输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# 设置动态库(.so/.dylib)输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if (MSVC)
    add_compile_options(/W3)
else ()
    add_compile_options(-Wall)
endif ()

find_package(OpenCV REQUIRED)

# 打印 OpenCV 信息（可选，用于调试）
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# 源文件列表
set(SOURCE_FILES
        src/main.cpp
        src/OpenCVVideoSource.cpp
        src/AsciiConverter.cpp
        src/LinuxRenderer.cpp
        src/WindowsRenderer.cpp
)

# 添加可执行文件
add_executable(bad_apple_ascii ${SOURCE_FILES})

# 包含头文件路径
target_include_directories(bad_apple_ascii PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${OpenCV_INCLUDE_DIRS}
)

# 链接库到目标
target_link_libraries(bad_apple_ascii PRIVATE
        ${OpenCV_LIBS}
)