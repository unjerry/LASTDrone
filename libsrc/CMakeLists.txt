cmake_minimum_required(VERSION 3.12)


aux_source_directory(${PROJECT_SOURCE_DIR}/libsrc/testLink testLinkDir)
add_library(testLink STATIC ${testLinkDir})

aux_source_directory(${PROJECT_SOURCE_DIR}/libsrc/gmWindow gmWindowDir)
add_library(gmWindow STATIC ${gmWindowDir})
target_link_libraries(gmWindow glfw glad)
