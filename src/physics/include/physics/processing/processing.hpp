#pragma once

#include "helpers/math.hpp"
// #include "physics/models/Track.hpp"
#include "physics/models/Vehicle.hpp"

#include <SFML/System.hpp>

namespace lf::physics::processing {

void process(models::Vehicle& vehicle)
{
    const auto steering_angle = vehicle.steering;
    sf::Vector2f steering_vect{helpers::sin_deg(steering_angle),
                               -helpers::sin_deg(steering_angle)};

    if (vehicle.accelerating > vehicle.braking) {
        // todo: core about resetting accelerating and braking values
        vehicle.acceleration += 1;
        if (vehicle.acceleration > vehicle.max_acceleration) {
            vehicle.acceleration = vehicle.max_acceleration;
        }
    } else if (vehicle.accelerating < vehicle.braking) {
        vehicle.acceleration -= 1;
        if (vehicle.acceleration < -vehicle.max_acceleration) {
            vehicle.acceleration = -vehicle.max_acceleration;
        }
    }

    vehicle.position.x += steering_vect.x * vehicle.acceleration;
    vehicle.position.y += steering_vect.y * vehicle.acceleration;

    vehicle.rotation += vehicle.acceleration;
}

} // namespace lf::physics::processing
