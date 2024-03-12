#pragma once
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "Game.h"
#include "Door.h"
class Camera
{
public:
    glm::vec3 position;
    glm::vec3 orientation;
    glm::vec3 up;
    float speed;
    float sensitivity;
    int width;
    int height;
    bool firstClick;
    bool insideHouse;
    

    Camera();
    void inputs(GLFWwindow* window);
    void changeCamera();
};

