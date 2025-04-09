//
// Created by Niccolo on 30/03/2025.
//

#include "interpreter.h"

#include <utility>

Interpreter::Interpreter(std::shared_ptr<Branch> branch, std::shared_ptr<Leaf> leaf, float angle, float radius, float length, float radius_decay, float length_decay) : radius(radius), length(length), radius_decay(radius_decay), length_decay(length_decay) {
    //this->builder_map['A'] = branch;
    //this->builder_map['a'] = branch;
    //this->builder_map['B'] = leaf;
    //this->builder_map['b'] = leaf;
    this->builder_map['F'] = branch;

    TurtleState s = TurtleState();
    s.position = glm::vec3(0.0f);
    s.direction = glm::vec3(0.0f, 1.0f, 0.0f);
    s.rotation = 0.0f;
    this->movement_step = 5.0f;
    this->angle = glm::radians(angle);
    this->state = s;
}

void Interpreter::read_string(const std::string &predicate, std::vector<Mesh>& meshes, std::vector<glm::mat4>& transforms) {
    TurtleState current =this->state;
    glm::mat4 rot;
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
                transforms.push_back(glm::rotate(glm::translate(glm::mat4(1.0f), this->state.position), glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
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
            case 'F':
                transforms.push_back(glm::rotate(glm::translate(glm::mat4(1.0f), current.position), current.rotation, glm::vec3(0.0f, 0.0f, 0.1f)));
                this->builder_map['F']->build_branch(this->length, this->radius, this->radius * radius_decay);
                this->state.position = current.position + this->movement_step * current.direction;
                current = this->state;
                this->radius *= this->radius_decay;
                //this->length *= this->length_decay;
                meshes.push_back(this->builder_map['F']->getResult());
                break;
            case '+':
                rot = glm::rotate(glm::mat4(1.0f), this->angle, glm::vec3(0.0f, 0.0f, 1.0f));
                this->state.direction = glm::normalize(glm::vec3(rot * glm::vec4(current.direction, 1.0f)));
                this->state.rotation += this->angle;
                current = this->state;
                break;
            case '-':
                rot = glm::rotate(glm::mat4(1.0f), -this->angle, glm::vec3(0.0f, 0.0f, 1.0f));
                this->state.direction = glm::normalize(glm::vec3(rot * glm::vec4(current.direction, 1.0f)));
                this->state.rotation -= this->angle;
                current = this->state;
                break;
            case '[':
                this->state_stack.push(current);
                break;
            case ']':
                this->state = this->state_stack.top();
                current = this->state;
                this->state_stack.pop();
                break;
            default:
                break;

        }
    }
}
