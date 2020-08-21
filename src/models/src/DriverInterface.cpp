#include "DriverInterface.hpp"

using namespace lf::models;

void DriverInterface::set_acceleration(Pedal pedal_press)
{
    accelerator_pedal = std::move(pedal_press);
}

void DriverInterface::set_braking(Pedal pedal_press)
{
    brake_pedal = std::move(pedal_press);
}

void DriverInterface::set_steering(SteeringWheel rotation)
{
    steering_wheel = std::move(rotation);
}

DriverView DriverInterface::get_view() const
{
    return DriverView{};
}
