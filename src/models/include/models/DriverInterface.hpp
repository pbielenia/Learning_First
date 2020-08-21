#pragma once

#include "helpers/NarrowedValue.hpp"

namespace lf::models {

using Pedal = lf::helpers::NarrowedValue<unsigned, 0U, 100U>;
using SteeringWheel = lf::helpers::NarrowedValue<int, -900, 900>;

struct DriverView {
    float front_distance;
};

class DriverInterface {
public:
    void set_acceleration(Pedal pedal_press);
    void set_braking(Pedal pedal_press);
    void set_steering(SteeringWheel rotation);
    const Pedal& get_acceleration() const noexcept;
    const Pedal& get_braking() const noexcept;
    const SteeringWheel& get_steering() const noexcept;
    DriverView get_view() const;

private:
    Pedal accelerator_pedal{0U};
    Pedal brake_pedal{0U};
    SteeringWheel steering_wheel{0U};
};

} // namespace lf::models
