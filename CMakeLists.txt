
cmake_minimum_required(VERSION 4.4)

project(VCM_SDK LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/bin
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/bin
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/bin
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG
        ${CMAKE_BINARY_DIR}/bin/debug
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE
        ${CMAKE_BINARY_DIR}/bin/release
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG
        ${CMAKE_BINARY_DIR}/bin/debug
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE
        ${CMAKE_BINARY_DIR}/bin/release
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG
        ${CMAKE_BINARY_DIR}/bin/debug
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE
        ${CMAKE_BINARY_DIR}/bin/release
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# ============================================================
# SDL3
# ============================================================

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.20
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(SDL3)


# ============================================================
# Dear ImGui
# ============================================================

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG docking
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(imgui)

add_library(imgui_lib SHARED
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp

        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlgpu3.cpp
)

target_include_directories(imgui_lib
        PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui_lib
        PUBLIC
        SDL3::SDL3
)


# ============================================================
# ImNodes
# ============================================================

FetchContent_Declare(
        imnodes
        GIT_REPOSITORY https://github.com/Nelarius/imnodes.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_SUBMODULES ""
        SOURCE_SUBDIR cmake_disabled
)

FetchContent_MakeAvailable(imnodes)

add_library(imnodes_lib SHARED
        ${imnodes_SOURCE_DIR}/imnodes.cpp
)

target_include_directories(imnodes_lib
        PUBLIC
        ${imnodes_SOURCE_DIR}
)

target_link_libraries(imnodes_lib
        PUBLIC
        imgui_lib
)


# ============================================================
# VCM SDK
# ============================================================

add_library(VCM-SDK SHARED
        src/DataTypes.cpp
        src/Node.cpp
)

target_include_directories(VCM-SDK
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(VCM-SDK
        PUBLIC
        imgui_lib
        imnodes_lib
)