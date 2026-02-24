/*
 * Name: Ahmmad Abdali Khan
 * Course: Computer Graphics Lab
 * Assignment: Draw a Cyan Star with Yellow Background
 */

#include "glad.h"
#include "glfw3.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Vertex Shader: Same as reference
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Fragment Shader: Modified to output CYAN (Red:0, Green:1, Blue:1)
const char *fragmentShaderCyanSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n" // Cyan
    "}\n\0";

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

    // Window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "0432320005101118", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Build and compile our shader program
    // Since both triangles are Cyan, we only need ONE shader program now
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderCyan = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramCyan = glCreateProgram();
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShaderCyan, 1, &fragmentShaderCyanSource, NULL);
    glCompileShader(fragmentShaderCyan);
    
    glAttachShader(shaderProgramCyan, vertexShader);
    glAttachShader(shaderProgramCyan, fragmentShaderCyan);
    glLinkProgram(shaderProgramCyan);

    // Clean up shaders as they are linked now
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderCyan);

    // Set up vertex data for a 6-Pointed Star
    // ------------------------------------------------------------------
    // Triangle 1: Pointing Upwards
    float firstTriangle[] = {
        -0.433f, -0.25f, 0.0f,  // bottom-left
         0.433f, -0.25f, 0.0f,  // bottom-right
         0.0f,    0.5f,  0.0f   // top
    };
    // Triangle 2: Pointing Downwards
    float secondTriangle[] = {
        -0.433f,  0.25f, 0.0f,  // top-left
         0.433f,  0.25f, 0.0f,  // top-right
         0.0f,   -0.5f,  0.0f   // bottom
    };

    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    // First triangle setup (Upward)
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Second triangle setup (Downward)
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Render Background (Yellow)
        // Yellow is Full Red (1.0) + Full Green (1.0) + No Blue (0.0)
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the Star
        glUseProgram(shaderProgramCyan);
        
        // Draw the first triangle (upward)
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // Draw the second triangle (downward)
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // De-allocate resources
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgramCyan);

    glfwTerminate();
    return 0;
}

// Process keyboard input
void processInput(GLFWwindow *window)
{
    // Close window if 'A' is pressed (First letter of Ahmmad)
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Resize viewport on window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}