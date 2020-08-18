#pragma once

namespace lf::models {

class Pedal {
public:
    using ValueType = unsigned;

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

    static ValueType narrow(ValueType to_narrow) noexcept;

    static const ValueType max_value{100U};
    static const ValueType min_value{0U};

    ValueType value{0U};
};

class DriverInterface {
public:
    //
private:
};

} // namespace lf::models
