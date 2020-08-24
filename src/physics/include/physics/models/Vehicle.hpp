#pragma once

#include <SFML/System.hpp>

namespace lf::physics::models {

struct Vehicle {
    Vehicle(unsigned max_speed, unsigned max_acceleration, const sf::Texture& texture)
        : max_speed{max_speed}, max_acceleration{max_acceleration}, sprite{texture}
    {
    }

    sf::Vector2f position{0.0f, 0.0f};
    float rotation{0.0f};
    float velocity{0.0f};
    float acceleration{0.0f};

    unsigned accelerating{0};
    unsigned braking{0};
    int steering{0};

    sf::Sprite sprite;

    const unsigned max_speed;
    const unsigned max_acceleration;
    const int max_steering{3};
};

} // namespace lf::physics::models
