#pragma once
#include "types.hpp"

void render_celestial_body(
    const CelestialBody &body,
    float meters_to_ndc_scale,
    int circle_segments);
