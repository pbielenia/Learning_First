#include "KeyboardInput.hpp"

#include <iostream>

using namespace lf::game::driver;

Steering KeyboardInput::get_steering([[maybe_unused]] const engine::DistanceMeter::Measures& measures)
{
    set_driver_choice();
    set_car_steering();
    return std::move(car_steering);
}

std::unique_ptr<Driver> KeyboardInput::create(const sf::Event& window_event)
{
    return std::make_unique<KeyboardInput>(window_event);
}

void KeyboardInput::set_driver_choice()
{
    switch (event.type) {
    case sf::Event::KeyPressed:
        switch (event.key.code) {
        case sf::Keyboard::Left: {
            driver_choice.direction = Choice::Direction::Left;
            break;
        }
        case sf::Keyboard::Right: {
            driver_choice.direction = Choice::Direction::Right;
            break;
        }
        default:
            break;
        }
        break;

    case sf::Event::KeyReleased:
        switch (event.key.code) {
        case sf::Keyboard::Left:
        case sf::Keyboard::Right: {
            driver_choice.direction = Choice::Direction::Straight;
            break;
        }
        default:
            break;
        }
        break;
    }
}

void KeyboardInput::set_car_steering()
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
