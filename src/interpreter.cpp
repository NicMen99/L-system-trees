//
// Created by Niccolo on 30/03/2025.
//

#include "interpreter.h"

#include <utility>

Interpreter::Interpreter(std::shared_ptr<Branch> builder) {
    this->builder_map['A'] = builder;
    this->builder_map['a'] = builder;
    this->builder_map['B'] = builder;
    this->builder_map['b'] = builder;

    TurtleState s = TurtleState();
    s.position = glm::vec3(0.0f);
    s.direction = glm::vec3(0.0f, 1.0f, 0.0f);
    s.up = glm::vec3(0.0f, 0.0f, 1.0f);
    this->movement_step = 5.0f;
    this->state = s;
}

std::vector<Mesh> Interpreter::read_string(const std::string &predicate) {
    std::vector<Mesh> result;
    TurtleState current =this->state;
    for (char c : predicate) {
        switch (c) {
            case 'A':
                this->builder_map['A']->build_branch(5.0f, 1.0f, 1.0f);
                this->state.position = current.position + this->movement_step * current.direction;
                current = this->state;
                result.push_back(this->builder_map['A']->getResult());
                break;
            case 'a':
                this->builder_map['a']->build_branch(2.0f, 1.0f, 1.0f);
                this->state.position = current.position + this->movement_step * current.direction;
                current = this->state;
                result.push_back(this->builder_map['a']->getResult());
                break;
            case 'B':
                this->builder_map['B']->build_branch(5.0f, 1.0f, 0.8f);
                this->state.position = current.position + this->movement_step * current.direction;
                current = this->state;
                result.push_back(this->builder_map['B']->getResult());
                break;
            case 'b':
                this->builder_map['b']->build_branch(2.0f, 1.0f, 0.8f);
                this->state.position = current.position + this->movement_step * current.direction;
                current = this->state;
                result.push_back(this->builder_map['b']->getResult());
                break;
            default:
                break;

        }
    }
    return result;
}
