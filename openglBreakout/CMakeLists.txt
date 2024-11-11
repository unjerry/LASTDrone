cmake_minimum_required(VERSION 3.12)
project(OGLBO)

# include path
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/glfw/include/)
include_directories(${CMAKE_SOURCE_DIR}/glm/)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRCDIR)
add_executable(gameBreakout "program.cpp" ${SRCDIR})
target_link_libraries(gameBreakout glad glfw gmWindow)

