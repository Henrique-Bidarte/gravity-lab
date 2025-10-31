#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

struct Ball
{
    float posX_m = 0.0f;
    float posY_m = 0.0f;
    float velX_mps = 0.0f;
    float velY_mps = 0.0f;
    float radius_m = 0.25f;

    float r = 1.0f, g = 1.0f, b = 1.0f;
};

static const float PI = 3.141593f;

void updatePhysics(Ball &ball, float dt, float gravity_mps2)
{
    ball.velY_mps += gravity_mps2 * dt;
    ball.posX_m += ball.velX_mps * dt;
    ball.posY_m += ball.velY_mps * dt;
}

void renderBall(const Ball &ball, float metersToNDC, int segments)
{
    float x_ndc = ball.posX_m * metersToNDC;
    float y_ndc = ball.posY_m * metersToNDC;
    float r_ndc = ball.radius_m * metersToNDC;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(ball.r, ball.g, ball.b);

    glVertex2f(x_ndc, y_ndc);

    for (int i = 0; i <= segments; ++i)
    {
        float angle = i * 2.0f * PI / segments;
        float x = r_ndc * cosf(angle);
        float y = r_ndc * sinf(angle);
        glVertex2f(x_ndc + x, y_ndc + y);
    }

    glEnd();
}

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow *window = glfwCreateWindow(800, 800, "Gravity Lab", nullptr, nullptr);
    if (!window)
        return -1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    const float metersToNDC = 0.02f;
    const int circleSegments = 4;
    const float GRAVITY = -9.81f;

    float lastTime = (float)glfwGetTime();

    Ball ball;
    ball.posX_m = 0.0f;
    ball.posY_m = 40.0f;
    ball.radius_m = 0.50f;
    ball.r = 1.0f;
    ball.g = 1.0f;
    ball.b = 1.0f;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        float now = (float)glfwGetTime();
        float dt = now - lastTime;
        lastTime = now;

        if (dt > 0.02f)
            dt = 0.02f;

        updatePhysics(ball, dt, GRAVITY);

        glClear(GL_COLOR_BUFFER_BIT);
        renderBall(ball, metersToNDC, circleSegments);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
