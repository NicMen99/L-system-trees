//
// Created by Niccolo on 29/03/2025.
//

#ifndef DRAWER_H
#define DRAWER_H

#include "mesh.h"

class Drawer {
public:
    virtual void build_branch(float height, float R, float r) {}
    virtual void build_leaf() {}
    virtual void build_terminal() {}

    virtual ~Drawer() = default;
    virtual Mesh getResult() {return Mesh();}
};

#endif //DRAWER_H
