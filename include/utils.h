//
// Created by Niccolo on 28/03/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../lib/stb_image.h"
#include <fstream>
#include "leaf_builder.h"
#include <map>

#include <iostream>
#include <cassert>

struct TreeConfig {
    std::map<char, std::map<std::string, float>> production_rules;
    const char* bark_texture_path;
    const char* leaf_texture_path;
    Type leaf_type;
    float branch_length;
    float branch_radius;
    float leaf_size;
    float radius_decay;
    float length_decay;
    int production_iterations;
    float alpha_discard;
    float angle;
    unsigned int resolution;
    std::string starting_production;
};

void error_callback(int error, const char* description);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);

unsigned int loadTexture(char const * path);

TreeConfig getConfig(const std::string& type);

#endif //UTILS_H
