#pragma once

#include "DistanceMeter.hpp"
#include "game/driver/Driver.hpp"
#include "game/environment/Environment.hpp"

#include <memory>

namespace lf::game::engine {

class Engine {
public:
    Engine(environment::Environment&& environment) : environment{environment}
    {
        if (!font.loadFromFile("/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf")) {
            throw std::runtime_error("Can not load font from file.");
        }
    }

    void run();
    void set_driver(std::unique_ptr<driver::Driver>);
    const sf::Event& get_event() const;

private:
    void analyze_event();
    void process_input();
    void process_models();
    void draw();
    void sleep();

    static std::string format_distance(const std::string& title, float distance);
    sf::Text create_text(float x, float y, const std::string& message);

    sf::RenderWindow window{sf::VideoMode(1920, 1080), "Learning First"};
    sf::Event event;

    driver::Steering steering;
    DistanceMeter::Measures measures;
    std::unique_ptr<driver::Driver> driver;
    environment::Environment environment;
    DistanceMeter distance_meter{environment.track.model.limits};
    sf::Font font;
};

} // namespace lf::game::engine
