#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

int WIDTH = 640;
int HEIGHT = 480;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (window) {
        glViewport(0, 0, width, height);
    }
    //std::cout << width << ' ' << height << '\n';
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

#ifdef NDEBUG 
extern "C" {
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

GLint create_shader_program(const char** vertex_shader, const char** fragment_shader) {
    GLint success;
    GLchar infoLog[512];

    GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, vertex_shader, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, fragment_shader, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit()) {
        return EXIT_FAILURE;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // vsync off
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGL()) {
        glfwTerminate();
        return EXIT_FAILURE;
    }
    std::cout << "Vendor:\t" << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Render:\t" << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL:\t" << glGetString(GL_VERSION) << std::endl;

    GLint shaderProgram1 = create_shader_program(&vertexShaderSource, &fragmentShaderSource1);
    GLint shaderProgram2 = create_shader_program(&vertexShaderSource, &fragmentShaderSource2);

    GLfloat vertices[] = {
        -0.9f,  -0.9f,  0.0f,
        -0.9f,  -0.7f,  0.0f,
        -0.7f,  -0.7f,  0.0f,
        -0.7f,  -0.9f,  0.0f
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3 
    };

    GLfloat first_triangle[] = {
        -0.5f,  -0.5f,  -0.5f,
        -0.5f,  0.5f,   0.0f,
        0.5f,   -0.5f,  0.0f
    };

    GLfloat second_triangle[] = {
        0.5f,  0.5f,  -0.5f,
        0.5f,  -0.5f,   0.0f,
        -0.5f,   0.5f,  0.0f
    };

    GLuint VAOs[2], VBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // first
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(first_triangle), first_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //second
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(second_triangle), second_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint VBO, VAO, EBO;
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

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(1, 1, 1, 1);
    auto time = std::chrono::high_resolution_clock::now();
    int f = 0;
    int shape = 0;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram1);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);

        glfwPollEvents();
        
        f++;
        if ((std::chrono::high_resolution_clock::now() - time).count() > 1e9) {
            std::cout << f << '\n';
            f = 0;
            time = std::chrono::high_resolution_clock::now();
            glPolygonMode(GL_FRONT_AND_BACK, shape++ % 2 == 0 ? GL_FILL : GL_LINE);
        }
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    
    glfwTerminate();

    system("pause");
    return EXIT_SUCCESS;
}
