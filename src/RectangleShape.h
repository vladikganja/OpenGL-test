#pragma once

#include "Shader.h"

class RectangleShape {
private:

    Shader shader;
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;

    float xOffset;
    float yOffset;
    float xPos;
    float yPos;

public:
    RectangleShape(float x, float y, float w, float h);
    RectangleShape(const RectangleShape& other) = delete;
    ~RectangleShape();

    void move(float x, float y);
    void setPosition(float x, float y);
    std::pair<float, float> getPosition();

    void setFillColor(float r, float g, float b);
    void draw();
};
