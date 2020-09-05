#include "Engine.hpp"

#include "physics/processing/processing.hpp"

#include <chrono>
#include <iostream>
#include <thread>

using namespace lf::game::engine;

void Engine::run()
{
    while (window.isOpen()) {
        do {
            process_input();
        } while (window.pollEvent(event));
        lines = distance_meter.get_lines(environment);
        process_models();
        draw();
        sleep();
    }
}

void Engine::set_driver(std::unique_ptr<driver::Driver> new_driver)
{
    driver = std::move(new_driver);
}

const sf::Event& Engine::get_event() const
{
    return event;
}

void Engine::process_input()
{
    if ((event.type == sf::Event::Closed)
        or (event.type == sf::Event::KeyPressed
            and event.key.code == sf::Keyboard::Escape)) {
        window.close();
    }
    steering = driver->get_steering();
}

void Engine::process_models()
{
    environment.car.set_steering(steering);
    physics::processing::process(environment.car.model, environment.track.model);
    environment.car.update_drawing();
}

void Engine::analyze_event()
{
    //
}

void Engine::draw()
{
    window.clear(sf::Color::Black);
    window.draw(environment.track.drawing);
    window.draw(environment.car.drawing);
    window.draw(lines.front);
    window.draw(lines.left);
    window.draw(lines.right);
    window.draw(lines.front_left);
    window.draw(lines.front_right);
    window.display();
}

void Engine::sleep()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}
