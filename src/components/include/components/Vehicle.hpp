#pragma once

#include "physics/models/Vehicle.hpp"

namespace lf::components {

class Vehicle {
public:
    Vehicle()
    {
        model.position.x = 500;
        model.position.y = 500;
    }

    void set_accelerating(unsigned pedal_press) noexcept
    {
        model.accelerating = pedal_press;
    }

    void set_braking(unsigned pedal_press) noexcept { model.braking = pedal_press; }

    void set_steering(int wheel_rotation) noexcept
    {
        model.steering = wheel_rotation / 18U;
    }

    physics::models::Vehicle& get_model() { return model; }

private:
    // drawing
    // model
    physics::models::Vehicle model{10, 2};
    // interface
};

} // namespace lf::components
