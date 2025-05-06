//
// Created by Niccolo on 07/04/2025.
//

#ifndef LEAF_BUILDER_H
#define LEAF_BUILDER_H

#include <memory>
#include <glm/vec4.hpp>
#include "abstract_builder.h"

class Leaf : public Drawer{
public:
    Leaf();
    ~Leaf() = default;
    void build_leaf(float size) override;
    std::shared_ptr<Mesh> getResult() override;
private:
    std::shared_ptr<Mesh> mesh;
    unsigned int tID;
};



#endif //LEAF_BUILDER_H
