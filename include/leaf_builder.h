//
// Created by Niccolo on 07/04/2025.
//

#ifndef LEAF_BUILDER_H
#define LEAF_BUILDER_H

#include <glm/vec4.hpp>
#include "abstract_builder.h"

class Leaf : public Drawer{
public:
    Leaf();
    ~Leaf() = default;
    void build_leaf(float size) override;
    Mesh getResult() override;
private:
    Mesh mesh;
    float size;
    unsigned int tID;
    //glm::vec4 color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
};



#endif //LEAF_BUILDER_H
