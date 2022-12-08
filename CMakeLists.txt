cmake_minimum_required(VERSION 3.2.0)

project(GawenenEngine VERSION 1.0)

file(GLOB source_files
    ${PROJECT_SOURCE_DIR}/Sources/*.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Core/*.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Entities/*.cpp
    ${PROJECT_SOURCE_DIR}/Sources/UI/*.cpp
    ${PROJECT_SOURCE_DIR}/Sources/UI/Components/*.cpp
    ${PROJECT_SOURCE_DIR}/Sources/UI/Micro/*.cpp
    ${PROJECT_SOURCE_DIR}/Sources/UI/Custom/*.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Map/*.cpp
    ${PROJECT_SOURCE_DIR}/Sources/States/*.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/*.cpp
    ${PROJECT_SOURCE_DIR}/Sources/Systems/Collision/*.cpp

    ${PROJECT_SOURCE_DIR}/Contents/*.cpp
    ${PROJECT_SOURCE_DIR}/Contents/Collectable/*.cpp
    ${PROJECT_SOURCE_DIR}/Contents/Skillchecks/*.cpp
)

set(SOURCES ${source_files})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} ${SOURCES})

target_precompile_headers(${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/Sources/stdpch.hpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE "C:/Program Files/SFML/include"
    PRIVATE ${PROJECT_SOURCE_DIR}/Sources
    PRIVATE ${PROJECT_SOURCE_DIR}/Contents
)

target_link_directories(${PROJECT_NAME}
    PRIVATE "C:/Program Files/SFML/lib"
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)