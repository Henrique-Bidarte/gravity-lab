#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <vector>

struct CelestialBody
{
    float position_x_meters = 0.0f;
    float position_y_meters = 0.0f;
    float velocity_x_meters_per_second = 0.0f;
    float velocity_y_meters_per_second = 0.0f;

    float radius_meters = 0.5f;
    float mass_kilograms = 1.0e14f;

    float color_red = 1.0f;
    float color_green = 1.0f;
    float color_blue = 1.0f;
};

static const float PI_const = 3.141593f;
static const double gravitational_constant_G = 6.67430e-11; // m^3 kg^-1 s^-2

void apply_mutual_gravity_and_integrate(
    CelestialBody &bodyA,
    CelestialBody &bodyB,
    float delta_time_seconds,
    float softening_distance_meters)
{
    double delta_x = (double)bodyB.position_x_meters - (double)bodyA.position_x_meters;
    double delta_y = (double)bodyB.position_y_meters - (double)bodyA.position_y_meters;

    double distance_squared = delta_x * delta_x + delta_y * delta_y +
                              (double)softening_distance_meters * (double)softening_distance_meters;

    double distance = std::sqrt(distance_squared);
    double inverse_distance_cubed = 1.0 / (distance_squared * distance);

    double accelerationA_x = gravitational_constant_G * (double)bodyB.mass_kilograms * delta_x * inverse_distance_cubed;
    double accelerationA_y = gravitational_constant_G * (double)bodyB.mass_kilograms * delta_y * inverse_distance_cubed;

    double accelerationB_x = -gravitational_constant_G * (double)bodyA.mass_kilograms * delta_x * inverse_distance_cubed;
    double accelerationB_y = -gravitational_constant_G * (double)bodyA.mass_kilograms * delta_y * inverse_distance_cubed;

    bodyA.velocity_x_meters_per_second += (float)(accelerationA_x * delta_time_seconds);
    bodyA.velocity_y_meters_per_second += (float)(accelerationA_y * delta_time_seconds);

    bodyB.velocity_x_meters_per_second += (float)(accelerationB_x * delta_time_seconds);
    bodyB.velocity_y_meters_per_second += (float)(accelerationB_y * delta_time_seconds);

    bodyA.position_x_meters += bodyA.velocity_x_meters_per_second * delta_time_seconds;
    bodyA.position_y_meters += bodyA.velocity_y_meters_per_second * delta_time_seconds;

    bodyB.position_x_meters += bodyB.velocity_x_meters_per_second * delta_time_seconds;
    bodyB.position_y_meters += bodyB.velocity_y_meters_per_second * delta_time_seconds;
}

void render_celestial_body(
    const CelestialBody &body,
    float meters_to_ndc_scale,
    int circle_segments)
{
    float position_ndc_x = body.position_x_meters * meters_to_ndc_scale;
    float position_ndc_y = body.position_y_meters * meters_to_ndc_scale;
    float radius_ndc = body.radius_meters * meters_to_ndc_scale;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(body.color_red, body.color_green, body.color_blue);

    glVertex2f(position_ndc_x, position_ndc_y);
    for (int segment_index = 0; segment_index <= circle_segments; ++segment_index)
    {
        float angle = segment_index * 2.0f * PI_const / circle_segments;
        glVertex2f(
            position_ndc_x + radius_ndc * cosf(angle),
            position_ndc_y + radius_ndc * sinf(angle));
    }
    glEnd();
}

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow *window = glfwCreateWindow(
        800, 800,
        "Gravity Lab",
        nullptr, nullptr);
    if (!window)
        return -1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glClearColor(0.02f, 0.02f, 0.04f, 1.0f);

    const float meters_to_ndc_conversion_scale = 0.02f;
    const int number_of_circle_segments = 24;
    const float gravitational_softening_distance_meters = 0.2f;

    std::vector<CelestialBody> celestial_bodies;

    CelestialBody body_A;
    body_A.mass_kilograms = 0.5e13f;
    body_A.radius_meters = 0.8f;
    body_A.position_x_meters = -20.0f;
    body_A.velocity_y_meters_per_second = -20.0f;
    celestial_bodies.push_back(body_A);

    CelestialBody body_B;
    body_B.mass_kilograms = 30.0e13f;
    body_B.radius_meters = 2.8f;
    celestial_bodies.push_back(body_B);

    CelestialBody body_C;
    body_C.mass_kilograms = 0.5e13f;
    body_C.radius_meters = 0.8f;
    body_C.position_x_meters = +20.0f;
    body_C.velocity_y_meters_per_second = +20.0f;
    celestial_bodies.push_back(body_C);

    float last_frame_time_seconds = (float)glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        float current_time_seconds = (float)glfwGetTime();
        float delta_time_seconds = current_time_seconds - last_frame_time_seconds;
        last_frame_time_seconds = current_time_seconds;

        if (delta_time_seconds > 0.01f)
            delta_time_seconds = 0.01f;

        for (int i = 0; i < (int)celestial_bodies.size(); ++i)
        {
            for (int j = i + 1; j < (int)celestial_bodies.size(); ++j)
            {
                apply_mutual_gravity_and_integrate(
                    celestial_bodies[i],
                    celestial_bodies[j],
                    delta_time_seconds,
                    gravitational_softening_distance_meters);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        for (const auto &body : celestial_bodies)
        {
            render_celestial_body(
                body,
                meters_to_ndc_conversion_scale,
                number_of_circle_segments);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
