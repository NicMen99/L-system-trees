cmake_minimum_required(VERSION 3.29)
project(L-system-trees)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/glfw-3.4)

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
        shaders/fshader.glsl
        shaders/vshader.glsl
        src/path_manager.cpp
        include/path_manager.h
        src/tree.cpp
        include/tree.h
)

target_include_directories(${PROJECT_NAME}
        PRIVATE lib/glfw-3.4/include
        lib/glad/include
        include)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} glm::glm)
