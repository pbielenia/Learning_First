#pragma once

#include "Car.hpp"
#include "Track.hpp"

namespace lf::game::environment {

struct Environment {
    Environment(Car&& car, Track&& track) : car{car}, track{track} {}

    Car car;
    Track track;
};

} // namespace lf::game::engine
