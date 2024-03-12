#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Player {
public:
    glm::vec3 position;
    float size;

    Player(glm::vec3 startPosition, float startSize) : position(startPosition), size(startSize) {}

    void handleInput(GLFWwindow* window) {
        float speed = 0.01f; // Define a speed for the movement
        float boundary = 10.0f; // Define the boundary of the plane

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && position.z - speed > -boundary)
            position.z -= speed; // Move forward
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && position.z + speed < boundary)
            position.z += speed; // Move backward
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && position.x - speed > -boundary)
            position.x -= speed; // Move left
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && position.x + speed < boundary)
            position.x += speed; // Move right
    }
};

