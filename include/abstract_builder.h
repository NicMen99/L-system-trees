//
// Created by Niccolo on 29/03/2025.
//

#ifndef DRAWER_H
#define DRAWER_H

#include "mesh.h"

class Drawer {
public:
    virtual void build_branch(float height, float R, float r) {}
    virtual void build_leaf(float size) {}
    virtual void build_junciton(float radius) {}

    virtual ~Drawer() = default;
    virtual std::shared_ptr<Mesh> getResult() {return std::make_shared<Mesh>();}
};

#endif //DRAWER_H
