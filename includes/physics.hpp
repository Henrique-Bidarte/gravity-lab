#pragma once
#include "types.hpp"

void apply_mutual_gravity_and_integrate(
    CelestialBody &bodyA,
    CelestialBody &bodyB,
    float delta_time_seconds,
    float softening_distance_meters);
