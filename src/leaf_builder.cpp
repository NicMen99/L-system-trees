//
// Created by Niccolo on 07/04/2025.
//

#include "leaf_builder.h"

Leaf::Leaf(float size) {
    this->size = size;
}

void Leaf::build_leaf() {
    std::vector<Vertex> vertices;

    glm::vec3 v1 = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 v2 = glm::vec3(this->size/2, this->size/2, 0.0f);
    glm::vec3 v3 = glm::vec3(-this->size/2, this->size/2, 0.0f);
    glm::vec3 v4 = glm::vec3(0.0f, this->size, 0.0f);

    vertices.push_back(Vertex{v2});
    vertices.push_back(Vertex{v1});
    vertices.push_back(Vertex{v4});

    vertices.push_back(Vertex{v3});
    vertices.push_back(Vertex{v4});
    vertices.push_back(Vertex{v1});

    this->mesh = Mesh(vertices, std::vector<unsigned int>{}, std::vector<Texture>{});
}

Mesh Leaf::getResult() {
    return this->mesh;
}
