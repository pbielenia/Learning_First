#include "models/Track.hpp"
#include "models/Vehicle.hpp"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <optional>
#include <thread>

static const auto pi = std::acos(-1);

float to_radians(float angle_in_degrees)
{
    static const auto multiplier = pi / 180.0f;
    return angle_in_degrees * multiplier;
}

float to_degrees(float angle_in_radians)
{
    static const auto multiplier = 180.0f / pi;
    return angle_in_radians * multiplier;
}

std::optional<sf::Texture> read_texture(const std::string& path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        return {};
    } else {
        return texture;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");

    auto car_texture = read_texture("images/car.png");
    lf::models::Vehicle car{car_texture.value(), 0.1f};
    car.set_position(500, 500);

    auto track_texture = read_texture("images/poznan_track.png");
    lf::models::Track track{track_texture.value()};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type = sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    car.rotate(-2);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    car.rotate(2);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    car.accelerate(1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    car.accelerate(-1);
                }
            }
        }

        window.clear(sf::Color::Black);

        car.update(0.02);

        track.draw_at(window);
        car.draw_at(window);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
