#pragma once

#include "Driver.hpp"

#include <memory>

namespace lf::game::driver {

class Bot : public Driver {
public:
    Steering get_steering(const engine::DistanceMeter::Measures& measures) override
    {
        set_driver_choice(measures);
        set_car_steering();
        return std::move(car_steering);
    }

    static std::unique_ptr<Driver> create() { return std::make_unique<Bot>(); }

private:
    void set_driver_choice(const engine::DistanceMeter::Measures& measures)
    {
        // calculate_reward(measures);
        // determine_state(measures);

        if (previous_measures.segment != measures.segment) {
            if (previous_measures.segment == engine::DistanceMeter::Segment::First
                    and measures.segment == engine::DistanceMeter::Segment::Second
                or previous_measures.segment == engine::DistanceMeter::Segment::Second
                       and measures.segment == engine::DistanceMeter::Segment::Third
                or previous_measures.segment == engine::DistanceMeter::Segment::Third
                       and measures.segment == engine::DistanceMeter::Segment::First) {
                std::cout << "Reward!\n";
            }
        }

        if (measures.out_of_track == true) {
            std::cout << "Penalty!\n";
        }

        if (measures.distances.front > measures.distances.front_left
            and measures.distances.front > measures.distances.left
            and measures.distances.front > measures.distances.front_right
            and measures.distances.front > measures.distances.right) {
            driver_choice.direction = Choice::Direction::Straight;
        } else if (measures.distances.right > measures.distances.left
                   and measures.distances.right > measures.distances.front_left) {
            driver_choice.direction = Choice::Direction::Right;
        } else if (measures.distances.left > measures.distances.front_right) {
            driver_choice.direction = Choice::Direction::Left;
        } else if (measures.distances.front_right > measures.distances.front_left) {
            driver_choice.direction = Choice::Direction::Right;
        } else {
            driver_choice.direction = Choice::Direction::Left;
        }

        previous_measures = measures;
    }

    void set_car_steering()
    {
        car_steering.accelerating = true;
        switch (driver_choice.direction) {
        case Choice::Direction::Right: {
            car_steering.wheels_angle = 1.0F;
            break;
        }
        case Choice::Direction::Left:
            car_steering.wheels_angle = -1.0F;
            break;

        case Choice::Direction::Straight:
            car_steering.wheels_angle = 0.0F;
            break;
        }
    }

    Choice driver_choice{};
    Steering car_steering{};

    engine::DistanceMeter::Measures previous_measures;
};

} // namespace lf::game::driver