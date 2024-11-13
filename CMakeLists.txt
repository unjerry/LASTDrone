cmake_minimum_required(VERSION 3.12)
project(sy2)
# static link command
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -s -mwindows")

# art resource path
configure_file(${PROJECT_SOURCE_DIR}/include/learnopengl/root_directory.h.in ${PROJECT_SOURCE_DIR}/include/learnopengl/root_directory.h)

# include path
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/glfw/include/)
include_directories(${PROJECT_SOURCE_DIR}/glm/)

# build binarys
add_subdirectory(glfw)

set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/glad")
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)
glad_add_library(glad REPRODUCIBLE MX API gl:core=4.3)


add_subdirectory(libsrc)

# build executable
add_executable(firstWindow src/firstWindow.cpp)
target_link_libraries(firstWindow glfw gmWindow glad)

add_executable(basicFinal src/basicFinal.cpp)
target_link_libraries(basicFinal glad glfw)

add_executable(multiwin_mx src/multiwin_mx.cpp)
target_link_libraries(multiwin_mx glad glfw)

add_executable(sumab src/testLink.cpp)
target_link_libraries(sumab testLink)

# subdirectory
add_subdirectory(leetcode)
add_subdirectory(openglBreakout)
if(MSVC)
    aux_source_directory(${PROJECT_SOURCE_DIR}/src/testsrc testsrcdir)
    add_executable(testsrc ${testsrcdir})

    add_subdirectory(torchPlayground)
endif()
