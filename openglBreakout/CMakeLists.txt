cmake_minimum_required(VERSION 3.12)
project(LASTDrone)

# include path
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/glfw/include/)
include_directories(${CMAKE_SOURCE_DIR}/glm/)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRCDIR)
add_executable(gameBreakout "program.cpp" ${SRCDIR})
target_link_libraries(gameBreakout glad glfw gmWindow assimp zlibstatic)

# add_executable(blend_discard "3.1.blending_discard/blending_discard.cpp")
# target_link_libraries(blend_discard glad glfw)
