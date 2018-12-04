cmake_minimum_required(VERSION 3.11)

project(keith)

file(GLOB KEITH_HEADERS src/headers/*.h)
file(GLOB KEITH_SOURCES src/*.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

add_executable(keith ${KEITH_HEADERS} ${KEITH_SOURCES})

target_link_libraries(keith sfml-window sfml-graphics sfml-audio)

target_include_directories(keith
    PUBLIC 
        $<INSTALL_INTERFACE:src/headers>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/headers>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)