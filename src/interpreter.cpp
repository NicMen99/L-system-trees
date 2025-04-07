//
// Created by Niccolo on 30/03/2025.
//

#include "interpreter.h"

#include <utility>

Interpreter::Interpreter(std::shared_ptr<Branch> branch, std::shared_ptr<Leaf> leaf) {
    this->builder_map['A'] = branch;
    this->builder_map['a'] = branch;
    this->builder_map['B'] = leaf;
    this->builder_map['b'] = leaf;

    TurtleState s = TurtleState();
    s.position = glm::vec3(0.0f);
    s.direction = glm::vec3(0.0f, 0.0f, 1.0f);
    s.up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->movement_step = 5.0f;
    this->state = s;
}

void Interpreter::read_string(const std::string &predicate, std::vector<Mesh>& meshes, std::vector<glm::mat4>& transforms) {
    TurtleState current =this->state;
    for (char c : predicate) {
        switch (c) {
            case 'A':
                transforms.push_back(glm::translate(glm::mat4(1.0f), this->state.position));
                this->builder_map['A']->build_branch(5.0f, 1.0f, 1.0f);
                this->state.position = current.position + this->movement_step * current.direction;
                current = this->state;
                meshes.push_back(this->builder_map['A']->getResult());
                break;
            case 'a':
                transforms.push_back(glm::translate(glm::mat4(1.0f), this->state.position));
                this->builder_map['a']->build_branch(2.0f, 1.0f, 1.0f);
                this->state.position = current.position + this->movement_step * current.direction;
                current = this->state;
                meshes.push_back(this->builder_map['a']->getResult());
                break;
            case 'B':
                transforms.push_back(glm::translate(glm::mat4(1.0f), this->state.position));
                this->builder_map['B']->build_leaf();
                this->state.position = current.position + this->movement_step * current.direction;
                current = this->state;
                meshes.push_back(this->builder_map['B']->getResult());
                break;
            case 'b':
                transforms.push_back(glm::translate(glm::mat4(1.0f), this->state.position));
                this->builder_map['b']->build_leaf();
                this->state.position = current.position + this->movement_step * current.direction;
                current = this->state;
                meshes.push_back(this->builder_map['b']->getResult());
                break;
            default:
                break;

        }
    }
}
