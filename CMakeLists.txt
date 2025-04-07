cmake_minimum_required(VERSION 3.29)
project(L-system-trees)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/glfw-3.4)
include_directories( SYSTEM lib/glad/include
                    include)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/glad.c
        src/utils.cpp
        include/utils.h
        src/camera.cpp
        include/camera.h
        src/lindenmayer.cpp
        include/lindenmayer.h
        include/abstract_builder.h
        include/branch_builder.h
        src/branch_builder.cpp
        src/interpreter.cpp
        include/interpreter.h
        src/mesh.cpp
        include/mesh.h
        src/shader.cpp
        include/shader.h
        src/leaf_builder.cpp
        include/leaf_builder.h
)

target_include_directories(${PROJECT_NAME} PRIVATE lib/glfw-3.4/include)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} glm::glm)
