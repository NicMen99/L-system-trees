//
// Created by Niccolo on 28/03/2025.
//

#include <iostream>
#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils.h"
#include "camera.h"
#include "interpreter.h"
#include "lindenmayer.h"
#include "shader.h"
#include "tree.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// FPS related values
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// MousePos related values
float lastx = 640, lasty = 360;
bool firstMouse = true;

// Camera
Camera camera(glm::vec3(0.0f, 2.0f, 15.0f));

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 12.0f,  0.0f, -15.0f),
    glm::vec3(-11.5f, 0.0f, -21.5f),
    glm::vec3(-31.8f, 0.0f, -12.3f),
    glm::vec3( 21.4f, 0.0f, -31.5f),
};

int main(int argc, char** argv) {
    glfwInit(); //Initialization of GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    stbi_set_flip_vertically_on_load(true);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "L-system trees", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // setting callback to resize viewport when resizing window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // This should be after window context is selected
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Allowing mouse input
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetScrollCallback(window, scroll_callback);

    // Setting depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CCW);

    Shader shader = Shader("shaders/vshader.glsl", "shaders/fshader.glsl");

    std::set<char> characters = {'P', 'F', 'L', '+', '-', '&', '^', '/', ')', '[', ']', 'X'};
    //std::map<char, std::vector<std::string>> production_rules ={
    //    {'P', std::vector<std::string> {"[&F[&&L]P[]F]/////[&F[&&L]P]///////[&F[&&L]P]", "[&F[&&L]P]/////////[&F[&&L]P]"}},
    //    {'F', std::vector<std::string> {"X/////%F", "XP%F", "F%F", "F", "FX%P"}},
    //    {'X', std::vector<std::string> {"F"}}
    //};

    std::map<char, std::vector<std::string>> production_rules ={
            {'F', std::vector<std::string> {"F[&%%%%%!!!!!F]F"}},
            {'X', std::vector<std::string> {"F"}}
        };

    //std::map<char, std::vector<std::string>> production_rules ={
    //    {'A', std::vector<std::string> {"FA", "FFA", "F[/////////&&&B][((((((((((&&&B]A", "FF", "F[/////&&&B][((((((((((((((&&&B]A", "F[/////////////&&&B]A", "F[//&&&B]A", "F[///////////////&&&B][////////////&&&B][//////&&&B]A"}},
    //    {'B', std::vector<std::string> {"!&FB", "!&FFB", "!&F", "!^FB", "!^FFB", "!^F", "!&X", "!^X"}},
    //    {'C', std::vector<std::string> {"&&&F"}},
    //    {'X', std::vector<std::string> {"F", "B"}}
    //};

    //std::map<char, std::string> production_rules = {
    //    {'X', "F[+X]F[-X]+X"},
    //    {'F', "FF"}
    //};
    auto l = Lindenmayer(characters, production_rules);

    std::vector<Tree> forest {};

    // Define tree construction variables
    float branch_length = 1.0f;
    float branch_radius = 0.1f;
    float leaf_size = 2.0f;

    std::unique_ptr<Branch> sBranch = std::make_unique<Branch>(20);
    std::unique_ptr<Leaf> sLeaf = std::make_unique<Leaf>();
    sBranch->build_branch(branch_length, branch_radius, branch_radius);
    sLeaf->build_leaf(leaf_size);

    std::shared_ptr<Mesh> branch_ptr = sBranch->getResult();
    std::shared_ptr<Mesh> leaf_ptr = sLeaf->getResult();

    sBranch->build_branch(0.5f * branch_length, branch_radius, branch_radius);
    std::shared_ptr<Mesh> end_ptr = sBranch->getResult();

    Interpreter turtle = Interpreter(22.5f, glm::vec3(0.0f), branch_radius, branch_length);

    for (glm::vec3 position : cubePositions) {
        turtle.reset_interpreter(position);
        std::vector<char> models {};
        std::vector<glm::mat4> transforms {};

        auto result = l.generate("F", 4, true);
        turtle.read_string(result, models, transforms);
        forest.emplace_back(transforms, models, branch_ptr, leaf_ptr, end_ptr);
    }

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // drawing until window closes RENDER LOOP
    while(!glfwWindowShouldClose(window)) {
        // Time calculations
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Clear screen
        // setting clear color
        glClearColor(0.5f, 0.5f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Inputs
        processInput(window);

        shader.use();
        shader.setVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        shader.setVec3("viewPos", camera.position);
        shader.setVec3("light.ambient", glm::vec3(0.7f, 0.7f, 0.7f));
        shader.setVec3("light.diffuse", glm::vec3(0.9f, 0.9f, 0.9f));
        // Camera settings
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 300.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // Stuff
        for (Tree tree: forest) {
            tree.render(shader);
        }

        // events and swap buffers
        glfwSwapBuffers(window); // swaps color buffer used to render to
        glfwPollEvents(); // Checking if events are triggered, updates window state and calls callbacks
    }

    shader.unuse();
    glfwTerminate(); // Terminate glfw, cleaning everything up
    return 0;
}