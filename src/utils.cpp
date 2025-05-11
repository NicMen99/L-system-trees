//
// Created by Niccolo on 28/03/2025.
//

#define STB_IMAGE_IMPLEMENTATION

#include "utils.h"
#include "camera.h"

extern Camera camera;
extern bool firstMouse;
extern float lastx, lasty;
extern float deltaTime;

void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.movementSpeed = 15.0f;
    }
    else {
        camera.movementSpeed = 2.5f;
    }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastx = xpos;
        lasty = ypos;
        firstMouse = false;
    }
    // Mouse position calculation
    float xoffset = xpos - lastx;
    float yoffset = lasty - ypos; // reversed because coordinates are flipped
    lastx = xpos;
    lasty = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

TreeConfig getConfig(const std::string& type) {
    std::map<std::string, TreeConfig> configurations = {
        {
            "Spruce", {
                {
            {
                    'F', std::map<std::string, float> {
                            {"X[[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]//[&&&&&!!!!!!B]//[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]][&&&&&!!!!!!B]//[&&&&&!!!!!!B]//[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]/[&&&&&!!!!!!B]//[&&&&&!!!!!!B]/[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]/[!!!!!!&&&&&B]//[&&&&&!!!!!!B]/[!!!!!!&&&&&B]]F[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]", 0.23},
                            {"X[/[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]//[&&&&&!!!!!!B]//[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]][&&&&&!!!!!!B]//[&&&&&!!!!!!B]//[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]/[&&&&&!!!!!!B]///[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]][&&&&&!!!!!!B]///[!!!!!!&&&&&B]F[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]", 0.23},
                            {"X[/[&&&&&!!!!!!B]/[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]][&&&&&!!!!!!B]//[&&&&&!!!!!!B]//[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]][&&&&&!!!!!!B]/[!!!!!!&&&&&B]/[&&&&&!!!!!!B]//[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]][&&&&&!!!!!!B]//[!!!!!!&&&&&B]//[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]]F[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]", 0.23},
                            {"X[//[&&&&&!!!!!!B]/[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]//[&&&&&!!!!!!B]//[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]][&&&&&!!!!!!B]//[&&&&&!!!!!!B]//[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]/[&&&&&!!!!!!B]//[!!!!!!&&&&&B]/[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]]F[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]", 0.23},
                            {"X[[&&&&&&L]////[&&&&&&L]////[&&&&&&L]////[&&&&&&L]]", 0.08}
                    }
                },
                {
                    'B', std::map<std::string, float> {
                            // {"X!%%[---L][////&&&L][+++L][((((&&&L]B", 1.0f},
                            {"X!%%[---/L][+++(L]B", 1.0f},
                        }
                    }
                },
                "textures/Bark_007_SD/Bark_007_BaseColor.jpg",
                "textures/Twigs.png",
                REGULAR,
                1.5f,
                0.2f,
                3.0f,
                0.85f,
                0.9f,
                7,
                0.6f,
                22.5f,
                16,
                "XXF"
            }
        },
        {
            "Hill", {
                {
                    {'P', std::map<std::string, float> {
                      {"[&F[&&L]PF]/////[&F[&&L]P]///////[&F[&&L]P]", 0.5},
                      {"[&F[&&L]P]/////////[&F[&&L]P]", 0.5}}},
                    {'F', std::map<std::string, float> {
                      {"X/////F", 0.2},
                      {"XPF", 0.2},
                      {"FF", 0.2},
                      {"F", 0.2},
                      {"FXP", 0.2}}},
                    {'X', std::map<std::string, float> {{"F", 1.0}}}
                },
                "textures/Bark_007_SD/Bark_007_BaseColor.jpg",
                "textures/Leaves.png",
                REGULAR,
                1.0f,
                0.1f,
                1.0f,
                0.9f,
                0.9f,
                7,
                0.9f,
                22.5f,
                16,
                "XF"
            }
        },
        {
            "Cactus", {
                {
                    {'F', std::map<std::string, float> {
                        {"F", 0.05},
                        {"FF", 0.6},
                        {"FJ", 0.1},
                        {"[B]F", 0.027},
                        {"[/B]F", 0.027},
                        {"[///B]F", 0.027},
                        {"[/////B]F", 0.027},
                        {"[///////B]F", 0.027},
                        {"[(B]F", 0.027},
                        {"[(((B]F", 0.027},
                        {"[(((((B]F", 0.027},
                        {"[(((((((B]F", 0.027}}
                    },
                    {'B', std::map<std::string, float> {{"!++++XJ----XF", 1.0}}}
                },
                "textures/cactus_0006_1k_8XvjS2/plants_0006_color_1k.jpg",
                "textures/Leaves.png",
                REGULAR,
                1.0f,
                0.4f,
                1.0f,
                0.9f,
                0.9f,
                4,
                0.9f,
                22.5f,
                16,
                "XF"
            }
        },
        {
            "Palm", {
                {
                    {
                        'F', std::map<std::string, float> {
                        {"^XX!F", 0.4},
                        {"XX!F", 0.4},
                        {"^!X", 0.1},
                        {"!X", 0.1}
                        }
                    },
                    {
                        'B', std::map<std::string, float> {
                        {"&X", 0.2},
                        {"//////&&X", 0.2},
                        {"/////////////////&X", 0.2},
                        {"//////////////////////////////////&X", 0.2},
                        {"///////////////////////////////////////////////////////&X", 0.2}
                        }
                    },
                    {
                        'T', std::map<std::string, float> {
                        {"J[^^^^^^^^^^^^^^^^^^^^L]//////////[^^^^^^^^^^^^^^^L]//////////[^^^^^^^^^^^^^^^^^^^^L]//////////[^^^^^^^^^^^^^^^L]//////////[^^^^^^^^^^^^^^^^^^^^L]//////////[^^^^^^^^^^^^^^^L]//////////[^^^^^^^^^^^^^^^^^^^^L]//////////[^^^^^^^^^^^^^^^L]", 1.0}
                        }
                    }
                },
                "textures/palm_tree_bark_1k/textures/palm_tree_bark_diff_1k.jpg",
                "textures/Palm.png",
                PALM,
                1.5f,
                0.4f,
                2.5f,
                0.9f,
                0.9f,
                5,
                0.5f,
                5.0f,
                16,
                "BXFT"
            }
        }
    };

    auto it = configurations.find(type);
    if (it != configurations.end()) {
        return it->second;
    }
    else {
        throw std::runtime_error("Errore: la configurazione richiesta non esiste.");
    }
}
