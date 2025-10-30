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

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 1.0f, 1.0f);

        glVertex2f(0.0f, 0.0f);

        for (int i = 0; i <= segments; i++)
        {
            float angle = i * 2.0f * PI / segments;
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            glVertex2f(x, y);
        }

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
