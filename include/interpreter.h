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

struct TurtleState {
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
};

class Interpreter {
public:
    Interpreter(std::shared_ptr<Branch> builder);
    ~Interpreter() = default;

    std::vector<Mesh> read_string(const std::string & predicate);
private:
    std::map<const char, std::shared_ptr<Drawer>> builder_map;
    float movement_step;
    TurtleState state;
};



#endif //INTERPRETER_H
