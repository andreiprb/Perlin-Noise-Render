cmake_minimum_required(VERSION 3.10)

project(PerlinNoiseRender VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(SOURCES
        source.cpp
        Renderer.cpp
        PerlinNoise.cpp
        color_vectors.cpp
)

set(HEADERS
        Renderer.h
        PerlinNoise.h
        color_vectors.h
        datatypes.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
