//
// Created by Niccolo on 30/03/2025.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <stack>

#include "abstract_builder.h"
#include "branch_builder.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "leaf_builder.h"

struct TurtleState {
    glm::vec3 position;
    glm::vec3 direction;
    float rotation;
};

class Interpreter {
public:
    Interpreter(std::shared_ptr<Branch> branch, std::shared_ptr<Leaf> leaf, float angle = 10.0f, float radius = 1.0f, float length = 5.0f, float radius_decay = 0.9f, float length_decay = 0.9f);
    ~Interpreter() = default;

    void read_string(const std::string & predicate, std::vector<Mesh>& meshes, std::vector<glm::mat4> & transforms);
private:
    std::map<const char, std::shared_ptr<Drawer>> builder_map;
    float radius, length;
    float length_decay, radius_decay;

    TurtleState state;
    std::stack<TurtleState> state_stack;
    float movement_step, angle;
};



#endif //INTERPRETER_H
