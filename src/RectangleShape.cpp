#include "RectangleShape.h"

RectangleShape::RectangleShape(float x, float y, float w, float h) : 
    xOffset(0.f), yOffset(0.f), xPos(x), yPos(y),
    shader("../../src/shaders/vertex.hlsl", "../../src/shaders/fragment1.hlsl") {

    GLfloat vertices[] = {
        x,      y - h,  0.0f,
        x,      y,      0.0f,
        x + w,  y,      0.0f,
        x + w,  y - h,  0.0f
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

RectangleShape::~RectangleShape() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void RectangleShape::move(float x, float y) {
    xOffset += x;
    yOffset += y;
    xPos += x;
    yPos += y;
    shader.setFloat("x", xOffset);
    shader.setFloat("y", yOffset);
}

void RectangleShape::setPosition(float x, float y) {
    xOffset = x - xPos + xOffset;
    yOffset = y - yPos + yOffset;
    xPos = x;
    yPos = y;
    shader.setFloat("x", xOffset);
    shader.setFloat("y", yOffset);
}

std::pair<float, float> RectangleShape::getPosition() {
    return { xPos, yPos };
}

void RectangleShape::setFillColor(float r, float g, float b) {
    shader.setFloat("r", r);
    shader.setFloat("g", g);
    shader.setFloat("b", b);
}

void RectangleShape::draw() {
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
