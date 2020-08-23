#pragma once

#include "helpers/math.hpp"
// #include "physics/models/Track.hpp"
#include "physics/models/Vehicle.hpp"

#include <SFML/System.hpp>
#include <iostream>

namespace lf::physics::processing {

void process(models::Vehicle& vehicle)
{
    const auto steering_angle = vehicle.steering;

    vehicle.rotation += steering_angle;
    while (vehicle.rotation < 0) {
        vehicle.rotation += 360;
    }
    if (vehicle.rotation > 360) {
        vehicle.rotation = static_cast<unsigned>(vehicle.rotation) % 360;
    }
    std::cout << "vehicle.rotation = " << vehicle.rotation << "\n";

    sf::Vector2f steering_vect{helpers::sin_deg(vehicle.rotation),
                               -helpers::cos_deg(vehicle.rotation)};

    std::cout << "vehicle.accelerating = " << vehicle.accelerating << "\n";
    std::cout << "vehicle.braking = " << vehicle.braking << "\n";
    std::cout << "vehicle.steering = " << vehicle.steering << "\n";

    if (vehicle.accelerating > vehicle.braking) {
        // todo: core about resetting accelerating and braking values
        vehicle.velocity += 0.2;
        if (vehicle.velocity > vehicle.max_speed) {
            vehicle.velocity = vehicle.max_speed;
        }
    } else if (vehicle.braking > vehicle.accelerating) {
        vehicle.velocity -= 0.1;
        if (vehicle.velocity < 0) {
            vehicle.velocity = 0;
        }
    }

    vehicle.accelerating = 0;
    vehicle.braking = 0;

    std::cout << "vehicle.velocity = " << vehicle.velocity << "\n";

    std::cout << "steering_angle = " << steering_angle << "\n";
    std::cout << "steering_vect.x = " << steering_vect.x << "\n";
    std::cout << "steering_vect.y = " << steering_vect.y << "\n";

    const auto translation =
        sf::Vector2f(steering_vect.x * static_cast<float>(vehicle.velocity),
                     steering_vect.y * static_cast<float>(vehicle.velocity));

    std::cout << "translation.x = " << translation.x << "\n";
    std::cout << "translation.y = " << translation.y << "\n";
    std::cout << "vehicle.position.x = " << vehicle.position.x << "\n";
    std::cout << "vehicle.position.y = " << vehicle.position.y << "\n";

    vehicle.position.x += translation.x;
    vehicle.position.y += translation.y;
}

} // namespace lf::physics::processing
