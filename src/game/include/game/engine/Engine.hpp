#pragma once

#include "game/driver/Driver.hpp"
#include "game/environment/Environment.hpp"

#include <memory>

namespace lf::game::engine {

class Engine {
public:
    Engine(environment::Environment&& environment) : environment{environment} {}

    void run();
    void set_driver(std::unique_ptr<driver::Driver>);
    const sf::Event& get_event() const;

private:
    void analyze_event();
    void process_input();
    void process_models();
    void draw();
    void sleep();

    sf::RenderWindow window{sf::VideoMode(1920, 1080), "Learning First"};
    sf::Event event;

    driver::Steering steering;
    std::unique_ptr<driver::Driver> driver;
    environment::Environment environment;
};

} // namespace lf::game::engine
