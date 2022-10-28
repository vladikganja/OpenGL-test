#include "RectangleShape.h"

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

    RectangleShape rect(-0.5f, 0.5f, 0.7f, 0.4f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(1, 1, 1, 1);

    GLfloat timeValue = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        timeValue = static_cast<GLfloat>(glfwGetTime());

        if (timeValue > 1.f) {
            rect.move(0.0001f, -0.0001f);
            rect.setFillColor(0.5f + sin(timeValue) / 2.f, 0.5f + cos(timeValue) / 2.f, 1.f);
        }

        rect.draw();
        
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    
    glfwTerminate();

    system("pause");
    return EXIT_SUCCESS;
}
