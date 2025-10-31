#include "render.hpp"
#include <GLFW/glfw3.h>
#include <cmath>

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
