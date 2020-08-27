#pragma once

#include "game/objects/Car.hpp"
#include "game/objects/Track.hpp"

namespace lf::game::engine {

struct DriverInput {
    bool is_accelerating{false};
    bool is_braking{false};
    bool is_turning_left{false};
    bool is_turning_right{false};
};

class Core {
public:
    Core(objects::Car&& car, objects::Track&& track) : car{car}, track{track} {}

    void run();

private:
    void analyze_event();
    void process_input();
    void process_models();
    void draw();
    void sleep();

    sf::RenderWindow window{sf::VideoMode(1920, 1080), "Learning First"};
    sf::Event event;
    DriverInput driver;

    objects::Car car;
    objects::Track track;
};

} // namespace lf::game::engine
