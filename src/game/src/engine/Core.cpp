#include "Core.hpp"

#include "physics/processing/processing.hpp"

#include <chrono>
#include <thread>

using namespace lf::game::engine;

void Core::run()
{
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            analyze_event();
        }
        process_input();
        process_models();
        draw();
        sleep();
    }
}

void Core::process_input()
{
    objects::Car::Steering steering{};

    if (driver.is_braking) {
        std::cout << "Braking\n";
        steering.braking = true;
    }
    if (driver.is_accelerating) {
        std::cout << "Accelerating\n";
        steering.accelerating = true;
    }
    if (driver.is_turning_left != driver.is_turning_right) {
        if (driver.is_turning_left) {
            std::cout << "Steering left\n";
            steering.wheels_angle = -1.0f;
        } else if (driver.is_turning_right) {
            std::cout << "Steering right\n";
            steering.wheels_angle = 1.0f;
        }
    }

    car.set_steering(steering);
}

void Core::process_models()
{
    physics::processing::process(car.model, track.model);
    car.update_drawing();
}

void Core::analyze_event()
{
    switch (event.type) {
    case sf::Event::Closed:
        window.close();
        break;

    case sf::Event::KeyPressed:
        switch (event.key.code) {
        case sf::Keyboard::Escape: {
            window.close();
            break;
        }
        case sf::Keyboard::Left: {
            driver.is_turning_left = true;
            break;
        }
        case sf::Keyboard::Right: {
            driver.is_turning_right = true;
            break;
        }
        case sf::Keyboard::Up: {
            driver.is_accelerating = true;
            break;
        }
        case sf::Keyboard::Down: {
            driver.is_braking = true;
            break;
        }
        default:
            break;
        }
        break;

    case sf::Event::KeyReleased:
        switch (event.key.code) {
        case sf::Keyboard::Left: {
            driver.is_turning_left = false;
            break;
        }
        case sf::Keyboard::Right: {
            driver.is_turning_right = false;
            break;
        }
        case sf::Keyboard::Up: {
            driver.is_accelerating = false;
            break;
        }
        case sf::Keyboard::Down: {
            driver.is_braking = false;
            break;
        }
        default:
            break;
        }
        break;
    }
}

void Core::draw()
{
    window.clear(sf::Color::Black);
    window.draw(track.drawing);
    window.draw(car.drawing);
    window.display();
}

void Core::sleep()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}
