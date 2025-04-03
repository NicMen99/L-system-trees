//
// Created by Niccolo on 30/03/2025.
//

#ifndef MESH_H
#define MESH_H
#include <vector>
#include <glm/vec3.hpp>
#include <glad/glad.h>


struct Vertex {
    glm::vec3 position;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh() = default;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void render();

    unsigned int VAO;

private:
    unsigned int VBO, EBO;
    void setupMesh();
};

#endif //MESH_H
