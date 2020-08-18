#include "DriverInterface.hpp"

using namespace lf::models;

auto Pedal::get_value() const noexcept -> ValueType
{
    return value;
}

auto Pedal::narrow(ValueType to_narrow) noexcept -> ValueType
{
    if (to_narrow > max_value) {
        return max_value;
    } else if (to_narrow < min_value) {
        return min_value;
    } else {
        return to_narrow;
    }
}
