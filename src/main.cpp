#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Error: GLFW\n";
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 800, "Gravity Lab", NULL, NULL);
    if (!window)
    {
        std::cerr << "Error: Window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    float radius = 0.2f;
    int segments = 4;
    const float PI = 3.141593f;

    float xPos = 0.0f;
    float yPos = 0.5f;
    float yVel = 0.0f;
    float gravity = -0.8f;

    while (!glfwWindowShouldClose(window))
    {
        yVel += gravity * 0.01f;
        yPos += yVel * 0.05f;

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 1.0f, 1.0f);

        glVertex2f(xPos, yPos);

        for (int i = 0; i <= segments; i++)
        {
            float angle = i * 2.0f * PI / segments;
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            glVertex2f(xPos + x, yPos + y);
        }

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
