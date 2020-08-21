// #include "collisions/Collision.hpp"
// #include "models/Track.hpp"
// #include "models/Vehicle.hpp"

#include "physics/processing/BasicProcessing.hpp"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <optional>
#include <thread>

// std::optional<sf::Texture> read_texture(const std::string& path)
// {
//     sf::Texture texture;
//     if (Collision::CreateTextureAndBitmask(texture, path) == false) {
//         return {};
//     } else {
//         return texture;
//     }
// }

static const auto pi = std::acos(-1);
static const auto to_rad_multiplier = pi / 180.0f;

int main()
{
    lf::physics::processing::BasicProcessing a;
    std::cout << "Learning First start\n";
    sf::RenderWindow window(sf::VideoMode(920, 1080), "Learning First");

    // const auto car_texture = read_texture("images/car.png");
    // const auto car_collision_texture = read_texture("images/car-wheels.png");
    // lf::models::Vehicle car{car_texture.value(), car_collision_texture.value(), 0.1f};
    // car.set_position(500, 500);

    // const auto track_texture = read_texture("images/custom_track.png");
    // const auto track_collision_texture = read_texture("images/custom_track-grass.png");
    // lf::models::Track track{track_texture.value(), track_collision_texture.value()};

    // bool accelerating{false};
    // bool braking{false};
    // bool rotating_left{false};
    // bool rotating_right{false};

    // sf::Image image;
    // if (image.loadFromFile("images/custom_track-grass.png") == false) {
    //     std::cout << "Reading image failed\n";
    //     return -1;
    // }

    // // auto pixels_pointer = image.getPixelsPtr();
    // // for (unsigned width = 0; width < image.getSize().x; ++width) {
    // //     for (unsigned height = 0; height < image.getSize().y; ++height) {
    // //         std::cout << image.getPixel(width, height).toInteger() << " ";
    // //     }
    // //     std::cout << "\n";
    // // }

    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         switch (event.type) {
    //         case sf::Event::Closed:
    //             window.close();
    //             break;

    //         case sf::Event::KeyPressed:
    //             switch (event.key.code) {
    //             case sf::Keyboard::Escape: {
    //                 window.close();
    //                 break;
    //             }
    //             case sf::Keyboard::Left: {
    //                 rotating_left = true;
    //                 break;
    //             }
    //             case sf::Keyboard::Right: {
    //                 rotating_right = true;
    //                 break;
    //             }
    //             case sf::Keyboard::Up: {
    //                 accelerating = true;
    //                 break;
    //             }
    //             case sf::Keyboard::Down: {
    //                 braking = true;
    //                 break;
    //             }
    //             default:
    //                 break;
    //             }
    //             break;

    //         case sf::Event::KeyReleased:
    //             switch (event.key.code) {
    //             case sf::Keyboard::Left: {
    //                 rotating_left = false;
    //                 break;
    //             }
    //             case sf::Keyboard::Right: {
    //                 rotating_right = false;
    //                 break;
    //             }
    //             case sf::Keyboard::Up: {
    //                 accelerating = false;
    //                 break;
    //             }
    //             case sf::Keyboard::Down: {
    //                 braking = false;
    //                 break;
    //             }
    //             default:
    //                 break;
    //             }
    //             break;
    //         }
    //     }

    //     if (braking != accelerating) {
    //         if (braking) {
    //             car.accelerate(-1.0f + car.get_velocity() / car.max_velocity);
    //         } else if (accelerating) {
    //             car.accelerate(1.0f - car.get_velocity() / car.max_velocity);
    //         }
    //     } else {
    //         const auto car_slowing = car.get_velocity() * 0.02f;
    //         car.accelerate((car_slowing) > 0.01f ? -car_slowing : -1.0f);
    //     }

    //     if (rotating_left != rotating_right) {
    //         if (rotating_left) {
    //             car.rotate(-2);
    //         } else if (rotating_right) {
    //             car.rotate(2);
    //         }
    //     }

    //     if (Collision::PixelPerfectTest(car.get_collision_sprite(),
    //                                     track.get_collision_sprite())) {
    //         car.accelerate(-0.5f);
    //     }

    //     window.clear(sf::Color::Black);

    //     car.update(0.02);

    //     auto driver_position(car.get_position());
    //     auto checking_point(driver_position);
    //     std::cout << "Driver position: " << driver_position.x << ", " <<
    //     driver_position.y
    //               << "\n";

    //     const auto car_rotation = car.get_rotation();

    //     while (checking_point.x > 0U && checking_point.x < image.getSize().x
    //            && checking_point.y > 0U && checking_point.y < image.getSize().y
    //            && image.getPixel(checking_point.x, checking_point.y)
    //                   == sf::Color::Transparent) {

    //         checking_point.x += std::sin(car_rotation * to_rad_multiplier);
    //         checking_point.y -= std::cos(car_rotation * to_rad_multiplier);
    //     }

    //     const sf::Vertex line[] = {sf::Vertex(driver_position),
    //                                sf::Vertex(checking_point)};

    //     std::cout << "Checking point: " << checking_point.x << ", " << checking_point.y
    //               << "\n";

    //     const auto line_length =
    //         std::sqrt((driver_position.x - checking_point.x)
    //                       * (driver_position.x - checking_point.x)
    //                   + (driver_position.y - checking_point.y)
    //                         * (driver_position.y - checking_point.y));
    //     std::cout << "Length: " << line_length << " px\n";

    //     track.draw_at(window);
    //     car.draw_at(window);
    //     window.draw(line, 2, sf::Lines);
    //     window.display();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(20));
    // }
}
