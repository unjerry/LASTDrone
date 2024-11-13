cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(example-app)

include (FetchContent)
set(FETCHCONTENT_QUIET off)
get_filename_component(torch_base "./torch_base"
                       REALPATH BASE_DIR "${PROJECT_SOURCE_DIR}")
set(FETCHCONTENT_BASE_DIR ${torch_base})
FetchContent_Declare(
  TCC
  URL https://download.pytorch.org/libtorch/cu124/libtorch-win-shared-with-deps-2.5.1%2Bcu124.zip
)
FetchContent_MakeAvailable(TCC)
# set(SDL2_PATH ${sdl2_SOURCE_DIR})

set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/torch_base/tcc-src)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(example-app example-app.cpp)
target_link_libraries(example-app "${TORCH_LIBRARIES}")
set_property(TARGET example-app PROPERTY CXX_STANDARD 17)

# The following code block is suggested to be used on Windows.
# According to https://github.com/pytorch/pytorch/issues/25457,
# the DLLs need to be copied to avoid memory errors.
if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET example-app
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:example-app>)
endif (MSVC)