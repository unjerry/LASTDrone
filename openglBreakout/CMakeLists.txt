cmake_minimum_required(VERSION 3.12)
project(LASTDrone)

# include path
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/glfw/include/)
include_directories(${CMAKE_SOURCE_DIR}/glm/)
include_directories(${CMAKE_SOURCE_DIR}/imgui/)
include_directories(${CMAKE_SOURCE_DIR}/imgui/backends)

aux_source_directory(${CMAKE_SOURCE_DIR}/imgui/ imghcpp)
add_library(gameBreakimgui STATIC ${imghcpp})
set(backendd
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRCDIR)
add_executable(gameBreakout "program.cpp" ${SRCDIR} ${backendd})
target_link_libraries(gameBreakout glad glfw gmWindow box2d gameBreakimgui)# assimp zlibstatic)

add_executable(b2Test "b2Test.cpp" ${SRCDIR} ${backendd})
target_link_libraries(b2Test glad glfw box2d gmWindow gameBreakimgui)
