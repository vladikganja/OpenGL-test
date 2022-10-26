#include "Shader.h"

int WIDTH = 640;
int HEIGHT = 480;

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
    __declspec(dllexport) unsigned long NvOptimusEnablement = 1;
    //__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

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

    Shader common_shader1("../../src/shaders/vertex.hlsl", "../../src/shaders/fragment1.hlsl");
    Shader common_shader2("../../src/shaders/vertex.hlsl", "../../src/shaders/fragment2.hlsl");
    Shader multicolored_shader("../../src/shaders/vertexMulticolored.hlsl", "../../src/shaders/fragmentMulticolored.hlsl");

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

    GLfloat multicolored_triangle[] = {
        -0.9f,  0.7f,   0.0f,   1.0f,   0.0f,   0.0f,
        -0.9f,  0.9f,   0.0f,   0.0f,   1.0f,   0.0f,
        -0.7f,  0.9f,   0.0f,    0.0f,   0.0f,  1.0f
    };

    GLfloat multicolored_rect[] = {
        0.7f,   0.7f,   0.0f,   1.0f,   0.0f,   0.0f,
        0.7f,   0.9f,   0.0f,   0.0f,   1.0f,   0.0f,
        0.9f,   0.9f,   0.0f,    0.0f,   0.0f,  1.0f,
        0.9f,   0.7f,   0.0f,    1.0f,   0.0f,  1.0f,
        0.85f,  0.65f,  0.0f,    1.0f,   1.0f,  1.0f
    };

    GLuint multiRectIndices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4
    };

    GLuint VAOs[2], VBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // first triangle
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(first_triangle), first_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // second triangle
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(second_triangle), second_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // multicolored triangle
    GLuint VBOmult, VAOmult;
    glGenVertexArrays(1, &VAOmult);
    glGenBuffers(1, &VBOmult);
    glBindVertexArray(VAOmult);
    glBindBuffer(GL_ARRAY_BUFFER, VBOmult);
    glBufferData(GL_ARRAY_BUFFER, sizeof(multicolored_triangle), multicolored_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // multicolored rect
    GLuint VBOmrect, VAOmrect, EBOmrect;
    glGenVertexArrays(1, &VAOmrect);
    glGenBuffers(1, &VBOmrect);
    glGenBuffers(1, &EBOmrect);
    glBindVertexArray(VAOmrect);
    glBindBuffer(GL_ARRAY_BUFFER, VBOmrect);
    glBufferData(GL_ARRAY_BUFFER, sizeof(multicolored_rect), multicolored_rect, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOmrect);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(multiRectIndices), multiRectIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // rect in the middle of the screen
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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(1, 1, 1, 1);
    auto time = std::chrono::high_resolution_clock::now();
    int f = 0;
    int shape = 0;
    float offset = 0.0f;
    int dx = 1;
    GLfloat timeValue = 0.0f;
    GLfloat timeDelta = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        timeDelta = timeValue;

        // color change
        timeValue = static_cast<GLfloat>(glfwGetTime());
        timeDelta = timeValue - timeDelta;
        GLfloat greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        common_shader2.setColor(0.0f, greenValue, 0.0f, 1.0f);

        // position change
        common_shader2.setFloat("xOffset", offset);
        offset += dx * timeDelta;
        if (offset > 0.5f && dx > 0 || offset < 0.0f && dx < 0) {
            dx *= -1;
        }

        common_shader1.use();
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        common_shader2.use();
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        common_shader1.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        multicolored_shader.use();
        glBindVertexArray(VAOmult);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        multicolored_shader.use();
        glBindVertexArray(VAOmrect);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        
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

    // shold become RAII class
    glDeleteVertexArrays(2, VAOs);
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &VAOmrect);
    glDeleteVertexArrays(1, &VAOmult);

    glDeleteBuffers(2, VBOs);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VBOmrect);
    glDeleteBuffers(1, &VBOmult);

    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &EBOmrect);
    
    glfwTerminate();

    system("pause");
    return EXIT_SUCCESS;
}
