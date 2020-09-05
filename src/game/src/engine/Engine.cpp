#include "Engine.hpp"

#include "physics/processing/processing.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

using namespace lf::game::engine;

void Engine::run()
{
    while (window.isOpen()) {
        do {
            process_input();
        } while (window.pollEvent(event));
        measures = distance_meter.get_measures(environment);
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
    window.draw(measures.lines.front);
    window.draw(measures.lines.left);
    window.draw(measures.lines.right);
    window.draw(measures.lines.front_left);
    window.draw(measures.lines.front_right);

    window.draw(
        create_text(0.0F, 0.0F, format_distance("front", measures.distances.front)));
    window.draw(
        create_text(0.0F, 25.0F, format_distance("left", measures.distances.left)));
    window.draw(
        create_text(0.0F, 50.0F, format_distance("right", measures.distances.right)));
    window.draw(
        create_text(0.0F,
                    75.0F,
                    format_distance("front_left", measures.distances.front_left)));
    window.draw(
        create_text(0.0F,
                    100.0F,
                    format_distance("front_right", measures.distances.front_right)));

    window.display();
}

void Engine::sleep()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

std::string Engine::format_distance(const std::string& title, float distance)
{
    std::ostringstream formatted_text;

    formatted_text << std::setw(13) << std::left << (title + ": ") << std::setw(4)
                   << std::setprecision(0) << std::fixed << std::right << distance;
    return formatted_text.str();
}

sf::Text Engine::create_text(float x, float y, const std::string& message)
{
    sf::Text text;
    text.setFont(font);
    text.setPosition(x, y);
    text.setCharacterSize(20);
    text.setString(message);
    return text;
}