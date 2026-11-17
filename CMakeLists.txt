cmake_minimum_required(VERSION 3.20)

project(UIN_Campus VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(uincampus
    src/version.cpp
)

target_include_directories(uincampus
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(uincampus
    PUBLIC UIN_VERSION="${PROJECT_VERSION}"
)

add_executable(uin-campus
    app/main.cpp
)

target_link_libraries(uin-campus PRIVATE uincampus)