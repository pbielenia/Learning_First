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

    sf::Vector2f position{0.0f, 0.0f};
    float rotation{0.0f};
    float velocity{0.0f};
    float acceleration{0.0f};

    bool accelerating{false};
    bool braking{false};
    float wheels_angle{0.0f};

    sf::Sprite wheels;

    const unsigned max_speed;
    const unsigned max_acceleration;
    const int max_steering{3};
};

} // namespace lf::physics::models
