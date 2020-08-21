#pragma once

#include <stdexcept>

namespace lf::helpers {

template<typename ValueType, ValueType lower_bound, ValueType upper_bound>
class NarrowedValue {
public:
    NarrowedValue()
    {
        if (lower_bound >= upper_bound) {
            std::runtime_error("Lower bound has to be greater than the upper bound.");
        }
    }

    template<typename T>
    NarrowedValue(T new_value) : value{narrow(to_value_type(new_value))}
    {
        if (lower_bound >= upper_bound) {
            std::runtime_error("Lower bound has to be greater than the upper bound.");
        }
    }

    ValueType get_value() const noexcept { return value; }

    template<typename T> void operator=(T new_value)
    {
        value = narrow(to_value_type(new_value));
    }

private:
    template<typename T> static ValueType to_value_type(T other)
    {
        return static_cast<ValueType>(other);
    }

    static ValueType narrow(ValueType to_narrow) noexcept
    {
        if (to_narrow > upper_bound) {
            return upper_bound;
        } else if (to_narrow < lower_bound) {
            return lower_bound;
        } else {
            return to_narrow;
        }
    }

    ValueType value{0U};
};

} // namespace lf::helpers
