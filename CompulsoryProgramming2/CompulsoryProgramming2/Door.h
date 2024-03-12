#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
class Door {
public:
    glm::vec3 position;
    bool isOpen;

    // Default constructor
    Door() : position(glm::vec3(-7.0f, 0.0f, -4.9f)), isOpen(false) {}
    
    // Constructor that takes a startPosition
    Door(glm::vec3 startPosition) : position(startPosition), isOpen(false) {}

    void open() {
        isOpen = true;
        //std::cout << "dør ska funk" << std::endl;
        // Add code here to animate the door opening
    }
};


