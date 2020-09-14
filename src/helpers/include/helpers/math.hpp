#pragma once

#include <cmath>

namespace lf::helpers {

static const auto pi = std::acos(-1);

template<typename T> T deg_to_rad(T degrees)
{
    static const auto multiplier = pi / 180.0f;
    return degrees * multiplier;
}

template<typename T> T rad_to_deg(T radians)
{
    static const auto multiplier = 180.0f / pi;
    return radians * multiplier;
}

static float sin_deg(float degrees)
{
    return std::sin(deg_to_rad(degrees));
}

static float cos_deg(float degrees)
{
    return std::cos(deg_to_rad(degrees));
}

} // namespace lf::helpers
