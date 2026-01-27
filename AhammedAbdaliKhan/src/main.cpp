/*
 * Name: Ahmmad Abdali Khan
 * Course: Computer Graphics Lab
 * Assignment: 01 - Hello Window
 */

#include "glad.h"
#include "glfw3.h"
#include <iostream>

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Window dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create the main window with my name
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ahmmad Abdali Khan", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL function pointers via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // Main render loop
    while (!glfwWindowShouldClose(window))
    {
        // Handle input
        processInput(window);

        // Render command
        // Background Color: Cyan (0.0f, 1.0f, 1.0f)
        glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers and poll for IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up resources
    glfwTerminate();
    return 0;
}

// Check for key presses
void processInput(GLFWwindow *window)
{
    // Close window if 'A' is pressed (First letter of name)
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Adjust viewport when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
