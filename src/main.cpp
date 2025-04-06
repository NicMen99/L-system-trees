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

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// FPS related values
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// MousePos related values
float lastx = 640, lasty = 360;
bool firstMouse = true;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, -5.0f));

int main() {
    glfwInit(); //Initialization of GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ProvaOpenGL", nullptr, nullptr);
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
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    Shader shader = Shader("shaders/vshader.glsl", "shaders/fshader.glsl");

    std::set<char> characters = {'A', 'a', 'B', 'b'};
    std::map<char, std::string> production_rules ={
        {'A', "aB" },
        {'a', "bA"},
        {'B', "A"},
        {'b', "a"}
    };
    auto l = Lindenmayer(characters, production_rules);

    auto result = l.generate("A", 3);
    //std::string result = "A";

    std::shared_ptr<Branch> sBranch = std::make_shared<Branch>(8);
    Interpreter turtle = Interpreter(sBranch);
    std::vector<Mesh> meshes;
    std::vector<glm::mat4> transforms;
    turtle.read_string(result, meshes, transforms);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // drawing until window closes RENDER LOOP
    while(!glfwWindowShouldClose(window)) {
        // Time calculations
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Clear screen
        // setting clear color
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Inputs
        processInput(window);

        shader.use();
        // Camera settings
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // Stuff
        for (int i = 0; i < meshes.size(); i++) {
            shader.setMat4("model", transforms[i]);
            meshes[i].render();
        }

        // events and swap buffers
        glfwSwapBuffers(window); // swaps color buffer used to render to
        glfwPollEvents(); // Checking if events are triggered, updates window state and calls callbacks
    }

    shader.unuse();
    glfwTerminate(); // Terminate glfw, cleaning everything up
    return 0;
}