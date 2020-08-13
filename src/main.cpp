#include "collisions/Collision.hpp"
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
    if (Collision::CreateTextureAndBitmask(texture, path) == false) {
        return {};
    } else {
        return texture;
    }
}

int main()
{
    std::cout << "Learning First start\n";
    sf::RenderWindow window(sf::VideoMode(1000, 1080), "My window");

    const auto car_texture = read_texture("images/car.png");
    const auto car_collision_texture = read_texture("images/car-wheels.png");
    lf::models::Vehicle car{car_texture.value(), car_collision_texture.value(), 0.1f};
    car.set_position(500, 500);

    const auto track_texture = read_texture("images/custom_track.png");
    const auto track_collision_texture = read_texture("images/custom_track-grass.png");
    lf::models::Track track{track_texture.value(), track_collision_texture.value()};

    bool accelerating{false};
    bool braking{false};
    bool rotating_left{false};
    bool rotating_right{false};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
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
                    rotating_left = true;
                    break;
                }
                case sf::Keyboard::Right: {
                    rotating_right = true;
                    break;
                }
                case sf::Keyboard::Up: {
                    accelerating = true;
                    break;
                }
                case sf::Keyboard::Down: {
                    braking = true;
                    break;
                }
                default:
                    break;
                }
                break;

            case sf::Event::KeyReleased:
                switch (event.key.code) {
                case sf::Keyboard::Left: {
                    rotating_left = false;
                    break;
                }
                case sf::Keyboard::Right: {
                    rotating_right = false;
                    break;
                }
                case sf::Keyboard::Up: {
                    accelerating = false;
                    break;
                }
                case sf::Keyboard::Down: {
                    braking = false;
                    break;
                }
                default:
                    break;
                }
                break;
            }
        }

        if (braking != accelerating) {
            if (braking) {
                car.accelerate(-1.0f + car.get_velocity() / car.max_velocity);
            } else if (accelerating) {
                car.accelerate(1.0f - car.get_velocity() / car.max_velocity);
            }
        } else {
            const auto car_slowing = car.get_velocity() * 0.02f;
            car.accelerate((car_slowing) > 0.01f ? -car_slowing : -1.0f);
        }

        if (rotating_left != rotating_right) {
            if (rotating_left) {
                car.rotate(-2);
            } else if (rotating_right) {
                car.rotate(2);
            }
        }

        if (Collision::PixelPerfectTest(car.get_collision_sprite(),
                                        track.get_collision_sprite())) {
            std::cout << "Collision!\n";
        } else {
            std::cout << "No collision!\n";
        }

        window.clear(sf::Color::Black);

        car.update(0.02);

        track.draw_at(window);
        car.draw_at(window);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
