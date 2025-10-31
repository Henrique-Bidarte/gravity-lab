#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Error initializing GLFW\n";
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 800, "Gravity Lab", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Error creating window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    const float metersToNDC = 0.02f; // NDC goes from -1 to 1, so 1 unit = 50 meters :D

    const float GRAVITY = -9.81f;

    float posX_meters = 0.0f;       // Horizontal position in meters
    float posY_meters = 40.0f;      // Vertical position in meters
    float velY_metersPerSec = 0.0f; // Vertical velocity in m/s
    float radius_meters = 0.50f;    // Object radius in meters

    const int circleSegments = 4;
    const float PI = 3.141593f;

    float lastFrameTime = (float)glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        if (deltaTime > 0.02f)
            deltaTime = 0.02f;

        // Apply gravity
        velY_metersPerSec += GRAVITY * deltaTime;     // v(t+dt) = v(t) + a*dt
        posY_meters += velY_metersPerSec * deltaTime; // y(t+dt) = y(t) + v*dt

        // ndc → normalized device coordinates
        float posX_ndc = posX_meters * metersToNDC;
        float posY_ndc = posY_meters * metersToNDC;
        float radius_ndc = radius_meters * metersToNDC;

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 1.0f, 1.0f);

        glVertex2f(posX_ndc, posY_ndc);

        for (int i = 0; i <= circleSegments; ++i)
        {
            float angle = i * 2.0f * PI / circleSegments;
            float x = radius_ndc * cosf(angle);
            float y = radius_ndc * sinf(angle);
            glVertex2f(posX_ndc + x, posY_ndc + y);
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
