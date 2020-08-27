#pragma once

#include "physics/models/Vehicle.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

namespace lf::components {

class Vehicle {
public:
    Vehicle(const sf::Texture& texture_view,
            const sf::Texture& texture_collision,
            float scale = 1.0f)
        : sprite{texture_view}, model{4, 1, texture_collision}
    {
        model.position.x = 500;
        model.position.y = 500;
        model.sprite.setPosition(500, 500);
        model.sprite.setScale(scale, scale);
        sprite.setPosition(500, 500);
        sprite.setScale(scale, scale);

        const auto texture_size = texture_view.getSize();
        sprite.setOrigin(texture_size.x / 2.0f, texture_size.y / 2.0f);
        model.sprite.setOrigin(texture_size.x / 2.0f, texture_size.y / 2.0f);
    }

    void set_accelerating(unsigned pedal_press) noexcept
    {
        model.accelerating = pedal_press;
    }

    void set_braking(unsigned pedal_press) noexcept { model.braking = pedal_press; }

    void set_steering(int wheel_rotation) noexcept
    {
        model.steering = wheel_rotation / 10;
    }

    void turn_wheel(int wheel_rotation_change) noexcept
    {
        model.steering += wheel_rotation_change;
        std::cout << "PRE model.steering = " << model.steering << "\n";
        if (model.steering > model.max_steering) {
            model.steering = model.max_steering;
        } else if (model.steering < -model.max_steering) {
            model.steering = -model.max_steering;
        }
    }

    void free_steering()
    {
        constexpr auto free_steering_change = 1;
        if (model.steering > free_steering_change) {
            model.steering -= free_steering_change;
        } else if (model.steering < -free_steering_change) {
            model.steering += free_steering_change;
        } else {
            model.steering = 0;
        }
    }

    void update()
    {
        sprite.setRotation(model.rotation);
        sprite.setPosition(static_cast<float>(model.position.x),
                           static_cast<float>(model.position.y));
        model.sprite.setRotation(model.rotation);
        model.sprite.setPosition(static_cast<float>(model.position.x),
                                 static_cast<float>(model.position.y));
    }

    physics::models::Vehicle& get_model() { return model; }
    const sf::Sprite& get_sprite() const { return sprite; }

private:
    // drawing
    sf::Sprite sprite;
    // model
    physics::models::Vehicle model;
    // interface
};

} // namespace lf::components
