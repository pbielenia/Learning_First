#include "Vehicle.hpp"

#include "helpers/math.hpp"

using namespace lf::models;

Vehicle::Vehicle(const sf::Texture& texture_view,
                 const sf::Texture& texture_collision,
                 float scale)
    : Drawable(texture_view, texture_collision, scale)
{
    set_origin(Drawable::get_middle());
}

void Vehicle::set_position(float x, float y)
{
    Drawable::set_position(x, y);
}

void Vehicle::update(float time_step_ms)
{
    const auto steering_angle = get_steering_angle();
    sf::Vector2f steering_vect{helpers::sin_deg(steering_angle),
                               -helpers::sin_deg(steering_angle)};
    Drawable::move(steering_vect * static_cast<float>(dynamics.velocity.get_value()));
    Drawable::set_rotation(steering_angle);
}

sf::Vector2f Vehicle::get_position() const
{
    return Drawable::get_position();
}

float Vehicle::get_rotation() const
{
    return Drawable::get_rotation();
}

float Vehicle::get_steering_angle() const
{
    return driver.get_steering().get_value() / 3;
}
