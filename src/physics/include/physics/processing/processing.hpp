#pragma once

#include "helpers/Collision.hpp"
#include "helpers/math.hpp"
#include "physics/models/Track.hpp"
#include "physics/models/Vehicle.hpp"

#include <SFML/System.hpp>
#include <iomanip>
#include <iostream>

namespace lf::physics::processing {

void process(models::Vehicle& vehicle, const models::Track& track)
{
    const auto steering_angle = vehicle.wheels_angle;

    vehicle.rotation += steering_angle;
    while (vehicle.rotation < 0) {
        vehicle.rotation += 360;
    }
    if (vehicle.rotation > 360) {
        vehicle.rotation = static_cast<unsigned>(vehicle.rotation) % 360;
    }

    sf::Vector2f steering_vect{helpers::sin_deg(vehicle.rotation),
                               -helpers::cos_deg(vehicle.rotation)};

    if (vehicle.velocity < 0) {
        vehicle.velocity = 0.0f;
    }

    if (vehicle.accelerating > vehicle.braking) {
        // todo: core about resetting accelerating and braking values
        vehicle.velocity += 0.2;
    } else if (vehicle.braking > vehicle.accelerating) {
        vehicle.velocity -= 0.1;

    } else {
        vehicle.velocity -= 0.02;
    }

    if (Collision::PixelPerfectTest(vehicle.wheels, track.limits) == true) {
        std::cout << "Out of the track!\n";
        vehicle.velocity -= (vehicle.velocity > 1.0f) ? 0.22f : 0.0f;
    } else {
        std::cout << "In the track\n";
    }

    std::cout << "Velocity: " << vehicle.velocity << "\n";

    if (vehicle.velocity > vehicle.max_speed) {
        vehicle.velocity = vehicle.max_speed;
    } else if (vehicle.velocity < 0) {
        vehicle.velocity = 0;
    }

    vehicle.accelerating = 0;
    vehicle.braking = 0;

    const auto translation =
        sf::Vector2f(steering_vect.x * static_cast<float>(vehicle.velocity),
                     steering_vect.y * static_cast<float>(vehicle.velocity));
    vehicle.position.x += translation.x;
    vehicle.position.y += translation.y;

    vehicle.wheels.setPosition(vehicle.position);
    vehicle.wheels.setRotation(vehicle.rotation);
}

} // namespace lf::physics::processing
