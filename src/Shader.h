#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <fstream>

class Shader {
    
private:
    enum class log_type {
        vertex_t,
        fragment_t,
        program_t
    };

    GLuint ID;
    void checkCompileErrors(GLuint shader, log_type type);

public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use();
    GLuint getID() const;
    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
};
