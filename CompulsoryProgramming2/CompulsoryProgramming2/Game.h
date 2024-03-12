#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Player.h"
#include "Pickup.h"
#include <vector>
#include "Camera.h"
#include "Door.h"

class Game {
public:
    Player player;
    Door door;
    Camera& camera;
    std::vector<Pickup> pickups;

    Game(Camera& camera) : player(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f), camera(camera) {
        // Initialize pickups with random positions
        for (int i = 0; i < 6; i++) {
            pickups.push_back(Pickup(glm::vec3(rand() % 10, 0.0f, rand() % 10)));
        }
    }



    void update(GLFWwindow* window) {
        player.handleInput(window);

        // Check for collisions between the player and the pickups
        for (auto it = pickups.begin(); it != pickups.end(); ) {
            if (glm::distance(player.position, it->position) < player.size) {
                // Collision detected, remove the pickup
                it = pickups.erase(it);
            }
            else {
                ++it;
            }
        }
        
        // Check for collision between the player and the door
        if (glm::distance(player.position, door.position) < player.size) {
            // Collision detected, open the door
            //door.open();
            //std::cout << "change plis" << std::endl;

            if (!camera.insideHouse) {
                camera.insideHouse = true;
                camera.changeCamera();
                std::cout << "how do you work" << std::endl;
            }
        }


        if (!camera.insideHouse) {
            camera.inputs(window);
        }
    }
};







