
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 
#include "Camera.h"
#include "Game.h"
#include "Pickup.h"
#include "Player.h"
#include "Door.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void checkShaderCompilation(GLuint shader) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

// Function to check program linking
void checkProgramLinking(GLuint program) {
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

int main() {

    Camera camera;
    Game game(camera);
    Player player(glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);
    Door door;

    // Initialize GLFW
    glfwInit();

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load OpenGL functions using glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    const char* vertexShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)glsl";

    
    const char* fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)glsl";

    const char* fragmentShaderSourceCube = R"glsl(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
}
)glsl";


    const char* fragmentShaderSourcePickup = R"glsl(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
)glsl";

    const char* fragmentShaderSourceHouse = R"glsl(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);
}
)glsl";


    const char* fragmentShaderSourceDoor = R"glsl(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}
)glsl";

    const char* fragmentShaderSourceObj = R"glsl(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}
)glsl";

    // Vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkShaderCompilation(vertexShader);

    // Fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkShaderCompilation(fragmentShader);


    //cube shader 
    unsigned int fragmentShaderCube = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderCube, 1, &fragmentShaderSourceCube, nullptr);
    glCompileShader(fragmentShaderCube);
    checkShaderCompilation(fragmentShaderCube);

    //pickup
    unsigned int fragmentShaderPickup = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderPickup, 1, &fragmentShaderSourcePickup, nullptr);
    glCompileShader(fragmentShaderPickup);
    checkShaderCompilation(fragmentShaderPickup);

    //House
    unsigned int fragmentShaderHouse = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderHouse, 1, &fragmentShaderSourceHouse, nullptr);
    glCompileShader(fragmentShaderHouse);
    checkShaderCompilation(fragmentShaderHouse);

    //Door
    unsigned int fragmentShaderDoor = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderDoor, 1, &fragmentShaderSourceDoor, nullptr);
    glCompileShader(fragmentShaderDoor);
    checkShaderCompilation(fragmentShaderDoor);

    //Sphere
    unsigned int fragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderObj, 1, &fragmentShaderSourceObj, nullptr);
    glCompileShader(fragmentShaderObj);
    checkShaderCompilation(fragmentShaderObj);

    // Shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLinking(shaderProgram);

    //Shader cube
    unsigned int shaderProgramCube = glCreateProgram();
    glAttachShader(shaderProgramCube, vertexShader);
    glAttachShader(shaderProgramCube, fragmentShaderCube);
    glLinkProgram(shaderProgramCube);
    checkProgramLinking(shaderProgramCube);

    //Shader Pickup
    unsigned int shaderProgramPickup = glCreateProgram();
    glAttachShader(shaderProgramPickup, vertexShader);
    glAttachShader(shaderProgramPickup, fragmentShaderPickup);
    glLinkProgram(shaderProgramPickup);
    checkProgramLinking(shaderProgramPickup);

    //Shader House
    unsigned int shaderProgramHouse = glCreateProgram();
    glAttachShader(shaderProgramHouse, vertexShader);
    glAttachShader(shaderProgramHouse, fragmentShaderHouse);
    glLinkProgram(shaderProgramHouse);
    checkProgramLinking(shaderProgramHouse);

    //Shader Door
    unsigned int shaderProgramDoor = glCreateProgram();
    glAttachShader(shaderProgramDoor, vertexShader);
    glAttachShader(shaderProgramDoor, fragmentShaderDoor);
    glLinkProgram(shaderProgramDoor);
    checkProgramLinking(shaderProgramDoor);

    //Shader Sphere
    unsigned int shaderProgramObj = glCreateProgram();
    glAttachShader(shaderProgramObj, vertexShader);
    glAttachShader(shaderProgramObj, fragmentShaderObj);
    glLinkProgram(shaderProgramObj);
    checkProgramLinking(shaderProgramObj);

    // Delete shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShaderCube);
    glDeleteShader(fragmentShaderPickup);
    glDeleteShader(fragmentShaderHouse);
    glDeleteShader(fragmentShaderDoor);
    glDeleteShader(fragmentShaderObj);





    float vertices[] = {
    -10.0f, -10.0f, 0.0f,  // bottom left
     10.0f, -10.0f, 0.0f,  // bottom right
     10.0f,  10.0f, 0.0f,  // top right
    -10.0f,  10.0f, 0.0f   // top left
    };

    unsigned int VBO, VAO;
    // Generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind VAO first
    glBindVertexArray(VAO);
    // Copy vertex data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Unbind VAO
    glBindVertexArray(0);


    //character
    float verticesCube[] = {
    -1.0f, -1.0f, -2.0f,  // 0
     1.0f, -1.0f, -2.0f,  // 1
     1.0f,  1.0f, -2.0f,  // 2
    -1.0f,  1.0f, -2.0f,  // 3
    -1.0f, -1.0f,  0.0f,  // 4
     1.0f, -1.0f,  0.0f,  // 5
     1.0f,  1.0f,  0.0f,  // 6
    -1.0f,  1.0f,  0.0f   // 7
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,  // front
        4, 5, 6, 6, 7, 4,  // back
        3, 2, 6, 6, 7, 3,  // top
        0, 1, 5, 5, 4, 0,  // bottom
        0, 3, 7, 7, 4, 0,  // left
        1, 2, 6, 6, 5, 1   // right
    };

    unsigned int VBO_cube, VAO_cube, EBO_cube;
    // Generate buffers
    glGenVertexArrays(1, &VAO_cube);
    glGenBuffers(1, &VBO_cube);
    glGenBuffers(1, &EBO_cube);
    // Bind VAO first
    glBindVertexArray(VAO_cube);
    // Copy vertex data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO_cube);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);
    // Copy index data to EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_cube);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Unbind VAO
    glBindVertexArray(0);

    //glEnable(GL_DEPTH_TEST);





    //House
    //Front wall
    float frontWallVertices[] = {
        -1.0f, -1.0f, -1.0f,  // Bottom left corner
         1.0f, -1.0f, -1.0f,  // Bottom right corner
         1.0f,  1.0f, -1.0f,  // Top right corner
        -1.0f,  1.0f, -1.0f   // Top left corner
    };

    //Back wall
    float backWallVertices[] = {
        -1.0f, -1.0f,  1.0f,  // Bottom left corner
         1.0f, -1.0f,  1.0f,  // Bottom right corner
         1.0f,  1.0f,  1.0f,  // Top right corner
        -1.0f,  1.0f,  1.0f   // Top left corner
    };

    //Left wall
    float leftWallVertices[] = {
        -1.0f, -1.0f, -1.0f,  // Bottom left corner
        -1.0f, -1.0f,  1.0f,  // Bottom right corner
        -1.0f,  1.0f,  1.0f,  // Top right corner
        -1.0f,  1.0f, -1.0f   // Top left corner
    };

    //Right wall
    float rightWallVertices[] = {
         1.0f, -1.0f, -1.0f,  // Bottom left corner
         1.0f, -1.0f,  1.0f,  // Bottom right corner
         1.0f,  1.0f,  1.0f,  // Top right corner
         1.0f,  1.0f, -1.0f   // Top left corner
    };

    //Roof
    float roofVertices[] = {
        -1.0f,  1.0f, -1.0f,  // Bottom left corner
         1.0f,  1.0f, -1.0f,  // Bottom right corner
         1.0f,  1.0f,  1.0f,  // Top right corner
        -1.0f,  1.0f,  1.0f   // Top left corner
    };

    unsigned int indicesHouse[] = {
    0, 1, 2,  // First triangle
    0, 2, 3   // Second triangle
    };


    unsigned int VAOs[5], VBOs[5], EBOs[5];
    glGenVertexArrays(5, VAOs);
    glGenBuffers(5, VBOs);
    glGenBuffers(5, EBOs);

    // Vertex arrays for each part of the house
    float* vertexArrays[5] = { frontWallVertices, backWallVertices, leftWallVertices, rightWallVertices, roofVertices };

    for (int i = 0; i < 5; i++) {
        // Bind the VAO
        glBindVertexArray(VAOs[i]);

        // Bind and set vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), vertexArrays[i], GL_STATIC_DRAW);

        // Bind and set element buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesHouse), indicesHouse, GL_STATIC_DRAW);

        // Configure vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    // Unbind the VAO
    glBindVertexArray(0);


    float doorVertices[] = {
        // Positions          
        -0.4f, 0.0f,  1.0f, // 8. door-left-bottom-front
         0.4f, 0.0f,  1.0f, // 9. door-right-bottom-front
         0.4f,  2.0f,  1.0f, // 10. door-right-top-front
        -0.4f,  2.0f,  1.0f  // 11. door-left-top-front
    };


    unsigned int doorIndices[] = {
        // Back face
        0, 1, 2,
        2, 3, 0,
    };

    // Generate VAO
    unsigned int VAO_Door;
    glGenVertexArrays(1, &VAO_Door);

    // Bind VAO
    glBindVertexArray(VAO_Door);

    // Generate VBO
    unsigned int VBO_Door;
    glGenBuffers(1, &VBO_Door);

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Door);

    // Copy vertex data into VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(doorVertices), doorVertices, GL_STATIC_DRAW);

    // Generate EBO
    unsigned int EBO_Door;
    glGenBuffers(1, &EBO_Door);

    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Door);

    // Copy index data into EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(doorIndices), doorIndices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO
    glBindVertexArray(0);

    
    // Define the vertices for the new cube
    float cubeObjVertices[] = {
        -0.5f, -0.5f, -0.5f,  // 0
         0.5f, -0.5f, -0.5f,  // 1
         0.5f,  0.5f, -0.5f,  // 2
        -0.5f,  0.5f, -0.5f,  // 3
        -0.5f, -0.5f,  0.5f,  // 4
         0.5f, -0.5f,  0.5f,  // 5
         0.5f,  0.5f,  0.5f,  // 6
        -0.5f,  0.5f,  0.5f   // 7
    };

    unsigned int cubeObjIndices[] = {
        0, 1, 2, 2, 3, 0,  // front
        4, 5, 6, 6, 7, 4,  // back
        3, 2, 6, 6, 7, 3,  // top
        0, 1, 5, 5, 4, 0,  // bottom
        0, 3, 7, 7, 4, 0,  // left
        1, 2, 6, 6, 5, 1   // right
    };

    // Generate buffers for the new cube
    unsigned int VBO_cubeObj, VAO_cubeObj, EBO_cubeObj;
    glGenVertexArrays(1, &VAO_cubeObj);
    glGenBuffers(1, &VBO_cubeObj);
    glGenBuffers(1, &EBO_cubeObj);

    // Bind the Vertex Array Object first
    glBindVertexArray(VAO_cubeObj);

    // Copy the vertex data to the Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, VBO_cubeObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeObjVertices), cubeObjVertices, GL_STATIC_DRAW);

    // Copy the index data to the Element Buffer Object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_cubeObj);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeObjIndices), cubeObjIndices, GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the Vertex Array Object
    glBindVertexArray(0);



    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        // Process input
        //camera.inputs(window);

        if (camera.insideHouse == false) {
            camera.inputs(window);
        }
        
        game.update(window);
        

        

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calculate view and projection matrices
        glm::mat4 view = glm::lookAt(camera.position, camera.position + camera.orientation, camera.up);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);



        

        // Draw the panel
        glUseProgram(shaderProgram);
        glm::mat4 model = glm::mat4(1.0f);  
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // Set uniforms for the panel
        GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // Draw House
        glUseProgram(shaderProgramHouse);
        GLint viewLocHouse = glGetUniformLocation(shaderProgramHouse, "view");
        glUniformMatrix4fv(viewLocHouse, 1, GL_FALSE, glm::value_ptr(view));
        GLint projLocHouse = glGetUniformLocation(shaderProgramHouse, "projection");
        glUniformMatrix4fv(projLocHouse, 1, GL_FALSE, glm::value_ptr(projection));
        for (int i = 0; i < 5; i++) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(-7.0f, 3.0f, -7.0f));  // Translate to top left
            model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));  // Set the new model matrix
            glBindVertexArray(VAOs[i]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }


        glUseProgram(shaderProgramDoor);
        //Draw door
        GLint viewLocDoor = glGetUniformLocation(shaderProgramDoor, "view");
        glUniformMatrix4fv(viewLocDoor, 1, GL_FALSE, glm::value_ptr(view));
        GLint projLocDoor = glGetUniformLocation(shaderProgramDoor, "projection");
        glUniformMatrix4fv(projLocDoor, 1, GL_FALSE, glm::value_ptr(projection));

        model = glm::mat4(1.0f); // start with the identity matrix
        model = glm::translate(model, glm::vec3(-7.0f, 0.0f, -4.9f));
        

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));  // Set the new model matrix
        glBindVertexArray(VAO_Door);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // Draw the cube
        glUseProgram(shaderProgramCube);
        // Create a model matrix for the cube
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), game.player.position);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translation * rotation;
        // Set uniforms for the cube
        modelLoc = glGetUniformLocation(shaderProgramCube, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        viewLoc = glGetUniformLocation(shaderProgramCube, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        projLoc = glGetUniformLocation(shaderProgramCube, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glBindVertexArray(VAO_cube);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        glUseProgram(shaderProgramObj);

        // Create a model matrix for the new cube
        glm::mat4 modelNewCube = glm::mat4(1.0f); // start with the identity matrix
        modelNewCube = glm::translate(modelNewCube, glm::vec3(-9.0f, 1.0f, -9.0f)); // position the new cube inside the house

        // Set the uniforms for the new cube
        GLint modelLocObj = glGetUniformLocation(shaderProgramObj, "model");
        glUniformMatrix4fv(modelLocObj, 1, GL_FALSE, glm::value_ptr(modelNewCube));
        GLint viewLocObj = glGetUniformLocation(shaderProgramObj, "view");
        glUniformMatrix4fv(viewLocObj, 1, GL_FALSE, glm::value_ptr(view));
        GLint projLocObj = glGetUniformLocation(shaderProgramObj, "projection");
        glUniformMatrix4fv(projLocObj, 1, GL_FALSE, glm::value_ptr(projection));

        // Bind the VAO and draw the new cube
        glBindVertexArray(VAO_cubeObj);
        glDrawElements(GL_TRIANGLES, sizeof(cubeObjIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);


        // Draw the pickups
        glUseProgram(shaderProgramPickup);  // Use the shader program for the pickups
        for (const auto& pickup : game.pickups) {
            // Create a model matrix for the pickup
            glm::mat4 translation = glm::translate(glm::mat4(1.0f), pickup.position);
            glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));  // Scale down by half
            model = translation * scale;  // Apply the scaling transformation
            // Set uniforms for the pickup
            modelLoc = glGetUniformLocation(shaderProgramPickup, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            viewLoc = glGetUniformLocation(shaderProgramPickup, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            projLoc = glGetUniformLocation(shaderProgramPickup, "projection");
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
            glBindVertexArray(VAO_cube);  // Bind the VAO for the cube
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);  // Draw the pickup
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO_cube);
    glDeleteBuffers(1, &VBO_cube);
    glDeleteBuffers(1, &EBO_cube);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgramCube);
    glDeleteProgram(shaderProgramPickup);
    glDeleteProgram(shaderProgramHouse);
    


    glfwTerminate();

    return 0;

}


