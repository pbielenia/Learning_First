#include "Vehicle.hpp"

#include <cmath>

using namespace lf::models;

Vehicle::Vehicle(const sf::Texture& texture, float scale) : Drawable(texture, scale)
{
    set_origin(Drawable::get_middle());
}

void Vehicle::set_position(float x, float y)
{
    Drawable::set_position(x, y);
}

void Vehicle::set_velocity(float velocity)
{
    this->velocity = velocity;
}

void Vehicle::rotate(float rotation_deg)
{
    static const auto pi = std::acos(-1);
    static const auto multiplier = pi / 180.0f;
    steering_rad += rotation_deg * multiplier;
}

void Vehicle::accelerate(float acceleration)
{
    velocity += acceleration;
}

void Vehicle::set_steering(float steering_deg)
{
    static const auto pi = std::acos(-1);
    static const auto multiplier = pi / 180.0f;
    steering_rad = steering_deg * multiplier;
}

void Vehicle::update(float time_step_ms)
{
    static const auto pi = std::acos(-1);
    static const auto multiplier = 180.0f / pi;

    sf::Vector2f steering_vect{std::sin(steering_rad), std::cos(steering_rad)};
    Drawable::move(steering_vect * velocity);
    Drawable::set_rotation(steering_rad * multiplier);
}
