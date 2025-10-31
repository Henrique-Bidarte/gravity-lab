#include "types.hpp"
#include <cmath>

void apply_mutual_gravity_and_integrate(
    CelestialBody &bodyA, CelestialBody &bodyB,
    float dt, float softening_m)
{
    double dx = (double)bodyB.position_x_meters - (double)bodyA.position_x_meters;
    double dy = (double)bodyB.position_y_meters - (double)bodyA.position_y_meters;

    double r2 = dx * dx + dy * dy + (double)softening_m * (double)softening_m;
    double r = std::sqrt(r2);
    double inv_r3 = 1.0 / (r2 * r);

    double axA = gravitational_constant_G * (double)bodyB.mass_kilograms * dx * inv_r3;
    double ayA = gravitational_constant_G * (double)bodyB.mass_kilograms * dy * inv_r3;
    double axB = -gravitational_constant_G * (double)bodyA.mass_kilograms * dx * inv_r3;
    double ayB = -gravitational_constant_G * (double)bodyA.mass_kilograms * dy * inv_r3;

    bodyA.velocity_x_meters_per_second += (float)(axA * dt);
    bodyA.velocity_y_meters_per_second += (float)(ayA * dt);
    bodyB.velocity_x_meters_per_second += (float)(axB * dt);
    bodyB.velocity_y_meters_per_second += (float)(ayB * dt);

    bodyA.position_x_meters += bodyA.velocity_x_meters_per_second * dt;
    bodyA.position_y_meters += bodyA.velocity_y_meters_per_second * dt;
    bodyB.position_x_meters += bodyB.velocity_x_meters_per_second * dt;
    bodyB.position_y_meters += bodyB.velocity_y_meters_per_second * dt;
}
