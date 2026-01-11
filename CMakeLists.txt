cmake_minimum_required(VERSION 3.28)
project(bad_apple_ascii)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if (MSVC)
    add_compile_options(/W3)
else ()
    add_compile_options(-Wall)
endif ()

find_package(OpenCV REQUIRED)

# 打印 OpenCV 信息（可选, 用于调试）
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# 源文件列表
set(SOURCE_FILES
        libs/miniaudio/miniaudio.c

        src/main.cpp
        src/OpenCVVideoSource.cpp
        src/AsciiConverter.cpp
        src/LinuxRenderer.cpp
        src/WindowsRenderer.cpp
        src/AsciiPlayer.cpp
        src/AudioPlayer.cpp
        include/AudioPlayer.hpp
)

# 添加可执行文件
add_executable(bad_apple_ascii ${SOURCE_FILES})

# 包含头文件路径
target_include_directories(bad_apple_ascii PRIVATE
        libs/miniaudio
        ${CMAKE_SOURCE_DIR}/include
        ${OpenCV_INCLUDE_DIRS}
)

# 链接库到目标
target_link_libraries(bad_apple_ascii PRIVATE
        ${OpenCV_LIBS}
)

# 链接系统库 (Linux 需要 pthread 和 dl, Miniaudio 可能会用到)
if (UNIX AND NOT APPLE)
    target_link_libraries(bad_apple_ascii PRIVATE pthread dl)
endif()

# 构建后自动复制资源到构建目录
add_custom_command(TARGET bad_apple_ascii POST_BUILD
        # 创建 resources 文件夹
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:bad_apple_ascii>/resources"
        # 复制内容到 resources 文件夹内
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:bad_apple_ascii>/resources"
        COMMENT "Copying resources to build directory structure..."
)

# 发布部署

# 安装可执行文件 -> 到根目录 (.)
install(TARGETS bad_apple_ascii
        RUNTIME DESTINATION .
)

# 安装资源文件 -> 到 resources 子目录
install(DIRECTORY "${CMAKE_SOURCE_DIR}/resources/"
        DESTINATION resources
        FILES_MATCHING PATTERN "*.*"
)

# 自动抓取并安装依赖 (DLLs/SOs) -> 到根目录 (.)
install(CODE [[
    # 设置搜索路径
    set(OPENCV_BIN_DIR "")
    if(WIN32)
        set(OPENCV_BIN_DIR "D:/libs/opencv/mingw_build/bin")
    endif()

    # 自动分析依赖
    file(GET_RUNTIME_DEPENDENCIES
        EXECUTABLES $<TARGET_FILE:bad_apple_ascii>
        RESOLVED_DEPENDENCIES_VAR _r_deps
        UNRESOLVED_DEPENDENCIES_VAR _u_deps
        DIRECTORIES ${OPENCV_BIN_DIR}
        POST_EXCLUDE_REGEXES ".*system32/.*" "^/lib" "^/usr/lib"
    )

    # 复制依赖库
    foreach(_file ${_r_deps})
        if(WIN32)
            if(_file MATCHES "\.dll$")
                message(STATUS "Deploying DLL: ${_file}")
                # [修改] 目标路径改为根目录 (之前是 bin)
                file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}" TYPE SHARED_LIBRARY FILES "${_file}")
            endif()
        else()
            if(_file MATCHES "\.so")
                message(STATUS "Deploying Lib: ${_file}")
                # [修改] 目标路径改为根目录
                file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}" TYPE SHARED_LIBRARY FILES "${_file}")
            endif()
        endif()
    endforeach()

    if(_u_deps)
        message(WARNING "Unresolved dependencies: ${_u_deps}")
    endif()
]])