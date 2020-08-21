#pragma once

#include "Drawable.hpp"
#include "DriverInterface.hpp"
#include "helpers/NarrowedValue.hpp"

namespace lf::models {

struct TechnicalSpecs {
    lf::helpers::NarrowedValue<unsigned, 0, 3000> weight;
};

struct DynamicQuantities {
    lf::helpers::NarrowedValue<unsigned, 0, 200> velocity;
};

class Vehicle : public Drawable {
public:
    Vehicle(const sf::Texture& texture_view,
            const sf::Texture& texture_collision,
            float scale = 1.0f);

    void set_position(float x, float y);
    void set_velocity(float velocity);
    void set_steering(float steering_deg);
    void rotate(float rotation_deg);
    void accelerate(float acceleration);
    void update(float time_step_ms);

    float get_velocity() const;
    sf::Vector2f get_position() const;
    float get_rotation() const;

    const float max_velocity{7.0f};
    const float min_velocity{0.0f};

    DriverInterface driver;
    TechnicalSpecs technical_specs;
    DynamicQuantities dynamics;

private:
    // float velocity{0.0f};
    // float steering_rad{0.0f};

    float get_steering_angle() const;

    sf::Vector2f last_position;
};

} // namespace lf::models
