//
// Created by Niccolo on 30/03/2025.
//

#include "branch_builder.h"

#include <cmath>
#include <iostream>
#include <glm/glm.hpp>

Branch::Branch(unsigned int resolution): resolution(resolution) {}

void Branch::build_branch(float height, float R, float r) {
    std::vector<Vertex> vertices;

    double increment = glm::radians(360.0f/(float)this->resolution);
    // Generating sides of Truncated cone
    for (int i = 0; i < this->resolution; i++) {
        double angleA = glm::radians(i*increment);
        double angleB = glm::radians((i+1)*increment);
        glm::vec3 v1(R * cos(i * increment), 0.0f, R * sin(i * increment));
        glm::vec3 v2(R * cos((i+1) * increment), 0.0f, R * sin((i+1) * increment));
        glm::vec3 v3(r * cos(i * increment), height, r * sin(i * increment));
        glm::vec3 v4(r * cos((i+1) * increment), height, r * sin((i+1) * increment));

        vertices.push_back(Vertex{v1});
        vertices.push_back(Vertex{v2});
        vertices.push_back(Vertex{v3});

        vertices.push_back(Vertex{v3});
        vertices.push_back(Vertex{v2});
        vertices.push_back(Vertex{v4});

        vertices.push_back(Vertex{glm::vec3(0, 0, 0)});
        vertices.push_back(Vertex{v1});
        vertices.push_back(Vertex{v2});

        vertices.push_back(Vertex{glm::vec3(0, height, 0)});
        vertices.push_back(Vertex{v4});
        vertices.push_back(Vertex{v3});
    }

    this->mesh = Mesh(vertices, std::vector<unsigned int>{});
}

Mesh Branch::getResult() {
    return this->mesh;
}
