#pragma once

#include <SFML/Graphics.hpp>

namespace lf::physics::models {

struct Vehicle {
    Vehicle(unsigned max_speed,
            unsigned max_acceleration,
            const sf::Texture& wheels_texture,
            float scale)
        : max_speed{max_speed}, max_acceleration{max_acceleration}, wheels{wheels_texture}
    {
        wheels.setScale(scale, scale);
    }

    sf::Vector2f position{0.0F, 0.0F};
    float rotation{0.0F};
    float velocity{0.0F};
    float acceleration{0.0F};

    bool accelerating{false};
    bool braking{false};
    float wheels_angle{0.0F};

    sf::Sprite wheels;

    unsigned max_speed;
    unsigned max_acceleration;
    const int max_steering{3};
};

} // namespace lf::physics::models
