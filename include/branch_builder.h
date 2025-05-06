//
// Created by Niccolo on 29/03/2025.
//

#ifndef BRANCH_BUILDER_H
#define BRANCH_BUILDER_H
#include <memory>
#include <glm/vec4.hpp>

#include "abstract_builder.h"

class Branch : public Drawer {
public:
    Branch(unsigned int resolution = 8);
    ~Branch() override = default;
    void build_branch(float height, float R, float r) override;
    std::shared_ptr<Mesh> getResult() override;

private:
    std::shared_ptr<Mesh> mesh;
    unsigned int resolution;
    unsigned int tID;
    //const glm::vec4 color = glm::vec4(0.6f, 0.3f, 0, 1);
};
#endif //BRANCH_BUILDER_H
