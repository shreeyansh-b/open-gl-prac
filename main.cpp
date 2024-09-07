#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm.hpp>

#include "Shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);




GLfloat vertices[] = {
    -0.5f,-0.75f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,
    0.0f, -0.75f, 0.0f,
    -0.5f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.5f, 0.75f, 0.0f,
    0.0f, 0.75f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.75f, 0.75f, 0.0f,
    0.75f, 0.5f, 0.0f
};

GLuint indices[] = {
    0,1,3,
    1,2,3,
    1,4,2,
    4,5,2,
    5,6,7,
    5,2,7,
    4,8,5,
    8,11,5,
    8,9,11,
    9,10,11,
    10,12,13,
    10,11,13
};


int main()
{

	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "openGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Window creation failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader ourShader("vert.hlsl", "frag.hlsl");




    // VAO, VBO, EBO etc.
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    int ourColorLocation = glGetUniformLocation(ourShader.ID, "ourColor");



    while (!glfwWindowShouldClose(window))
    {
        processInput(window);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue * 0.5f) / 2.0f) + 0.5f;  // Slowed down
        float redValue = (tan(timeValue * 0.1f) / 1.25f) + 0.33f;  // Much slower to avoid sharp changes
        float blueValue = (cos(timeValue * 0.5f) / 2.55f) + 0.69f; // Slowed down

        glUniform4f(ourColorLocation, redValue, greenValue, blueValue, 1.0f);

        ourShader.Activate();
        glBindVertexArray(VAO);
        // 36 is how many vertices to draw
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}