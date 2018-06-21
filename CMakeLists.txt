cmake_minimum_required (VERSION 3.0)
project (LoopSubdivision)

include_directories (${CMAKE_SOURCE_DIR}/libs/glew-2.0.0/include/GL
                     ${CMAKE_SOURCE_DIR}/libs/freeglut-3.0.0/include/GL)

file (GLOB_RECURSE PROJECT_HEADERS src/*.hpp
           			src/*.h)

file (GLOB_RECURSE PROJECT_SOURCES src/*.cpp
                                   src/*.c)

file (GLOB_RECURSE PROJECT_SHADERS src/*.fs
                                   src/*.vs)

file (GLOB         PROJECT_CONFIGS CMakeLists.txt
                                   README.rst
                                  .gitignore
                                  .gitmodules)

source_group ("headers" FILES ${PROJECT_HEADERS})
source_group ("shaders" FILES ${PROJECT_SHADERS})
source_group ("sources" FILES ${PROJECT_SOURCES})
source_group ("vendors" FILES ${VENDORS_SOURCES})

#link_directories(${CMAKE_SOURCE_DIR}/libs/freeglut-3.0.0/build/lib/Debug)
#link_directories(${CMAKE_SOURCE_DIR}/libs/glew-2.0.0/build/lib/Debug)

link_directories(${CMAKE_CURRENT_BINARY_DIR}/lib/Debug)

#set(ENV{PATH} "${CMAKE_SOURCE_DIR}/libs/glew-2.0.0/build/bin/Debug;${CMAKE_SOURCE_DIR}/libs/freeglut-3.0.0/build/bin/Debug")
set(ENV{PATH} "${CMAKE_CURRENT_BINARY_DIR}/bin/Debug")

add_executable (${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                                ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                                ${VENDORS_SOURCES})

add_subdirectory(libs/freeglut-3.0.0)
add_subdirectory(libs/glew-2.0.0)