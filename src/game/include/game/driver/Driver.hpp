#pragma once

#include "game/environment/Car.hpp"
#include "game/engine/DistanceMeter.hpp"

namespace lf::game::driver {

struct Choice {
    enum class Direction { Left, Right, Straight };
    Direction direction{Direction::Straight};
};

using Steering = environment::Car::Steering;

struct Driver {
    virtual Steering get_steering(const engine::DistanceMeter::Measures&) = 0;
};

} // namespace lf::game::driver
