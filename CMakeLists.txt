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

if(WIN32)
    # 设置 opencv 路径
    set(OpenCV_DIR "D:/libs/opencv/mingw_install")
    set(OPENCV_BIN_DIR "D:/libs/opencv/mingw_build/bin")
endif()

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

if(WIN32)
    # 在 Windows 下添加资源文件
    list(APPEND SOURCE_FILES res/icon.rc)
endif()

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
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:bad_apple_ascii>/resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:bad_apple_ascii>/resources"
        COMMENT "Copying resources for development..."
)

# 发布部署 (Install 逻辑)

# 安装二进制文件
install(TARGETS bad_apple_ascii RUNTIME DESTINATION .)

# 安装资源 (保持 resources 目录结构)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/resources/" DESTINATION resources)

# 依赖处理
if(WIN32)
    # 找到并安装 opencv_videoio_ffmpeg DLL
    # 使用 GLOB 模糊匹配，这样版本号变了也能找到 (例如 4120, 480 等)
    file(GLOB FFMPEG_DLL "${OPENCV_BIN_DIR}/opencv_videoio_ffmpeg*.dll")

    if(FFMPEG_DLL)
        message(STATUS "Found FFmpeg DLL: ${FFMPEG_DLL}")
        install(FILES ${FFMPEG_DLL} DESTINATION .)
    else()
        message(WARNING "Could not find opencv_videoio_ffmpeg DLL in ${OPENCV_BIN_DIR}")
    endif()

    # 动态获取编译器的 bin 目录
    get_filename_component(COMPILER_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    # 把 CMake 变量传递给 Install 脚本
    install(CODE "set(COMPILER_BIN_DIR \"${COMPILER_BIN_DIR}\")")
    install(CODE "set(OPENCV_BIN_DIR \"${OPENCV_BIN_DIR}\")")

    # 自动抓取其他隐式依赖 (opencv_world, libstdc++ 等)
    install(CODE [[
        # 打印路径 (调试用)
        message(STATUS "Searching for DLLs in:")
        message(STATUS "   > Compiler: ${COMPILER_BIN_DIR}")
        message(STATUS "   > OpenCV:   ${OPENCV_BIN_DIR}")

        file(GET_RUNTIME_DEPENDENCIES
            EXECUTABLES $<TARGET_FILE:bad_apple_ascii>
            RESOLVED_DEPENDENCIES_VAR _r_deps
            UNRESOLVED_DEPENDENCIES_VAR _u_deps
            # 把编译器目录加入搜索列表
            DIRECTORIES "${OPENCV_BIN_DIR}" "${COMPILER_BIN_DIR}"
            POST_EXCLUDE_REGEXES ".*system32/.*"
        )

        foreach(_file ${_r_deps})
            # 只复制 DLL
            if(_file MATCHES "\.dll$")
                # 排除已经手动复制的 ffmpeg dll，防止冲突
                if(NOT _file MATCHES "opencv_videoio_ffmpeg")
                    message(STATUS "Deploying Dependency: ${_file}")
                    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}" TYPE SHARED_LIBRARY FILES "${_file}")
                endif()
            endif()
        endforeach()

        if(_u_deps)
            message(WARNING "Unresolved dependencies: ${_u_deps}")
        endif()
    ]])

elseif(UNIX AND NOT APPLE)
    # --- Linux 策略 ---
    message(STATUS "Linux deployment: Relying on system libraries")
endif()