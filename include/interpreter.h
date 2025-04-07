//
// Created by Niccolo on 30/03/2025.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <memory>
#include <string>
#include <vector>
#include <map>

#include "abstract_builder.h"
#include "branch_builder.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "leaf_builder.h"

struct TurtleState {
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
};

class Interpreter {
public:
    Interpreter(std::shared_ptr<Branch> branch, std::shared_ptr<Leaf> leaf);
    ~Interpreter() = default;

    void read_string(const std::string & predicate, std::vector<Mesh>& meshes, std::vector<glm::mat4> & transforms);
private:
    std::map<const char, std::shared_ptr<Drawer>> builder_map;
    float movement_step;
    TurtleState state;
};



#endif //INTERPRETER_H
