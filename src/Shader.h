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
    void checkCompileErrors(unsigned int shader, log_type type);

public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use();
    GLuint get();

};
