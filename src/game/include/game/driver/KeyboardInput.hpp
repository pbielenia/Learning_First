#pragma once

#include "Driver.hpp"

#include <SFML/Window.hpp>

namespace lf::game::driver {

class KeyboardInput : public Driver {
public:
    explicit KeyboardInput(const sf::Event& window_event) : event{window_event} {}

    Steering get_steering() override;
    static std::unique_ptr<Driver> create(const sf::Event& window_event);

private:
    void set_driver_choice();
    void set_car_steering();

    const sf::Event& event;
    Choice driver_choice{};
    Steering car_steering{};
};

} // namespace lf::game::driver
