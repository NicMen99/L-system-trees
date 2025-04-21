//
// Created by Niccolo on 30/03/2025.
//

#ifndef MESH_H
#define MESH_H
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "shader.h"


struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
};

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh() = default;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void render(Shader &shader);

    unsigned int VAO;

private:
    unsigned int VBO, EBO;
    void setupMesh();
};

#endif //MESH_H
