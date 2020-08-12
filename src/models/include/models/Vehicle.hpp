#pragma once

#include "Drawable.hpp"

namespace lf::models {

class Vehicle : public Drawable {
public:
    Vehicle(const sf::Texture& texture, float scale = 1.0f);

    void set_position(float x, float y);
    void set_velocity(float velocity);
    void set_steering(float steering_deg);
    void rotate(float rotation_deg);
    void accelerate(float acceleration);
    void update(float time_step_ms);

    float get_velocity() const;

private:
    const float max_velocity{2.0f};
    const float min_velocity{0.0f};

    float velocity{0.0f};
    float steering_rad{0.0f};

    sf::Vector2f last_position;
};

} // namespace lf::models
