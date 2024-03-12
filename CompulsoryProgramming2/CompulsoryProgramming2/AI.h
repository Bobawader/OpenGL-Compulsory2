#pragma once
#include <vector>
#include <numeric>
#include "Camera.h"

class AI {
public:
    glm::vec3 CurrentAIPosition;
    std::vector<float> x_values;  
    std::vector<float> y_values;  
    float a, b;  

    AI(const std::vector<float>& x_values, const std::vector<float>& y_values)
        : x_values(x_values), y_values(y_values) {
        calculateLeastSquaresFit();
    }

    void calculateLeastSquaresFit() {
        float x_sum = std::accumulate(x_values.begin(), x_values.end(), 0.0f);
        float y_sum = std::accumulate(y_values.begin(), y_values.end(), 0.0f);
        float xy_sum = std::inner_product(x_values.begin(), x_values.end(), y_values.begin(), 0.0f);
        float x_square_sum = std::inner_product(x_values.begin(), x_values.end(), x_values.begin(), 0.0f);
        int n = x_values.size();

        a = (n * xy_sum - x_sum * y_sum) / (n * x_square_sum - x_sum * x_sum);
        b = (y_sum - a * x_sum) / n;
    }

    float f(float x) {
        return a * x + b;
    }

    void MoveAI(glm::vec3 pos) {
        CurrentAIPosition = pos;
    }

    glm::mat4 CalculateModelMatrix() {
        return glm::translate(glm::mat4(1.f), CurrentAIPosition);
    }


    //i started with the ai and function but i never got it to work
};
