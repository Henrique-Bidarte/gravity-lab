#pragma once
#include <cstdint>

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

inline constexpr float PI_const = 3.141593f;
inline constexpr double gravitational_constant_G = 6.67430e-11;
