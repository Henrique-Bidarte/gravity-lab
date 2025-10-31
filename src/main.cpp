#include <GLFW/glfw3.h>
#include <vector>
#include <cstdio>
#include "types.hpp"
#include "physics.hpp"
#include "render.hpp"

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow *window = glfwCreateWindow(800, 800, "Gravity Lab", nullptr, nullptr);
    if (!window)
        return -1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    const float meters_to_ndc_conversion_scale = 0.02f;
    const int number_of_circle_segments = 24;
    const float gravitational_softening_distance_m = 0.8f;

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

    float simulation_time_seconds = 0.0f;
    int fps_frame_count = 0;
    float fps_time_accumulator = 0.0f;
    const float fps_update_interval = 0.25f;

    while (!glfwWindowShouldClose(window))
    {
        float current_time_seconds = (float)glfwGetTime();
        float delta_time_seconds = current_time_seconds - last_frame_time_seconds;
        last_frame_time_seconds = current_time_seconds;

        if (delta_time_seconds > 0.01f)
            delta_time_seconds = 0.01f;

        simulation_time_seconds += delta_time_seconds;

        for (int i = 0; i < (int)celestial_bodies.size(); ++i)
        {
            for (int j = i + 1; j < (int)celestial_bodies.size(); ++j)
            {
                apply_mutual_gravity_and_integrate(
                    celestial_bodies[i],
                    celestial_bodies[j],
                    delta_time_seconds,
                    gravitational_softening_distance_m);
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

        fps_frame_count += 1;
        fps_time_accumulator += delta_time_seconds;
        if (fps_time_accumulator >= fps_update_interval)
        {
            float fps = (float)fps_frame_count / fps_time_accumulator;
            char title_buf[128];
            std::snprintf(title_buf, sizeof(title_buf),
                          "Gravity Lab — FPS: %.1f — Time: %.2fs",
                          fps, simulation_time_seconds);
            glfwSetWindowTitle(window, title_buf);

            fps_frame_count = 0;
            fps_time_accumulator = 0.0f;
        }
    }

    glfwTerminate();
    return 0;
}
