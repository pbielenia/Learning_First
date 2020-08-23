#include "collisions/Collision.hpp"
// #include "models/Track.hpp"
// #include "models/Vehicle.hpp"

#include "components/Vehicle.hpp"
#include "physics/processing/processing.hpp"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <optional>
#include <thread>

std::optional<sf::Texture> read_texture(const std::string& path)
{
    sf::Texture texture;
    if (Collision::CreateTextureAndBitmask(texture, path) == false) {
        return {};
    } else {
        return texture;
    }
}

struct DriverInput {
    bool is_accelerating{false};
    bool is_braking{false};
    bool is_turning_left{false};
    bool is_turning_right{false};
};

struct Game {

    Game(lf::components::Vehicle vehicle,
         std::function<void(const DriverInput&, lf::components::Vehicle&)> process_input)
        : vehicle{std::move(vehicle)}, process_input{process_input}

    {
    }

    void run()
    {
        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                analyze_event();
            }
            process_input(driver_input, vehicle);
            lf::physics::processing::process(vehicle.get_model());
            vehicle.update_sprite();
            draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }

    void analyze_event()
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
                driver_input.is_turning_left = true;
                break;
            }
            case sf::Keyboard::Right: {
                driver_input.is_turning_right = true;
                break;
            }
            case sf::Keyboard::Up: {
                driver_input.is_accelerating = true;
                break;
            }
            case sf::Keyboard::Down: {
                driver_input.is_braking = true;
                break;
            }
            default:
                break;
            }
            break;

        case sf::Event::KeyReleased:
            switch (event.key.code) {
            case sf::Keyboard::Left: {
                driver_input.is_turning_left = false;
                break;
            }
            case sf::Keyboard::Right: {
                driver_input.is_turning_right = false;
                break;
            }
            case sf::Keyboard::Up: {
                driver_input.is_accelerating = false;
                break;
            }
            case sf::Keyboard::Down: {
                driver_input.is_braking = false;
                break;
            }
            default:
                break;
            }
            break;
        }
    }

    void draw()
    {
        window.clear(sf::Color::Black);
        window.draw(vehicle.get_sprite());
        window.display();
    }

    sf::RenderWindow window{sf::VideoMode(920, 1080), "Learning First"};
    sf::Event event;
    lf::components::Vehicle vehicle;
    std::function<void(const DriverInput&, lf::components::Vehicle&)> process_input;
    DriverInput driver_input;
};

int main()
{
    std::cout << "Learning First start\n";

    const auto car_texture = read_texture("images/car.png");
    lf::components::Vehicle vehicle{car_texture.value(), 0.1f};
    // todo: Vehicle should't make accesible its model,
    //       may be instead derive from some abstract class,
    //       which has an attribute "model" or a virtual method "get_model()".

    // Next:
    //      1. Check if model works properly without graphics.
    //      2. Create graphical vehicle representation.
    //      3. Create a track model and graphical representation.
    //      4. Connect the whole to drive a car using keyboard.
    //      5. Handle collisions.
    //      6. Draw the line.
    //      7. Draw the lines.

    // const auto car_texture = read_texture("images/car.png");
    // const auto car_collision_texture = read_texture("images/car-wheels.png");
    // lf::models::Vehicle car{car_texture.value(), car_collision_texture.value(), 0.1f};
    // car.set_position(500, 500);

    // const auto track_texture = read_texture("images/custom_track.png");
    // const auto track_collision_texture = read_texture("images/custom_track-grass.png");
    // lf::models::Track track{track_texture.value(), track_collision_texture.value()};

    Game game{std::move(vehicle),
              [](const DriverInput& driver, lf::components::Vehicle& vehicle) {
                  if (driver.is_braking) {
                      std::cout << "Braking\n";
                      vehicle.set_braking(100);
                  }
                  if (driver.is_accelerating) {
                      std::cout << "Accelerating\n";
                      vehicle.set_accelerating(100);
                  }
                  if (driver.is_turning_left != driver.is_turning_right) {
                      if (driver.is_turning_left) {
                          std::cout << "Steering left\n";
                          vehicle.turn_wheel(-1);
                      } else if (driver.is_turning_right) {
                          std::cout << "Steering right\n";
                          vehicle.turn_wheel(1);
                      }
                  } else {
                      std::cout << "Steering straight\n";
                      vehicle.free_steering();
                  }
              }};

    game.run();

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

    // if (braking != accelerating) {
    //     if (braking) {
    //         car.accelerate(-1.0f + car.get_velocity() / car.max_velocity);
    //     } else if (accelerating) {
    //         car.accelerate(1.0f - car.get_velocity() / car.max_velocity);
    //     }
    // } else {
    //     const auto car_slowing = car.get_velocity() * 0.02f;
    //     car.accelerate((car_slowing) > 0.01f ? -car_slowing : -1.0f);
    // }

    // if (rotating_left != rotating_right) {
    //     if (rotating_left) {
    //         car.rotate(-2);
    //     } else if (rotating_right) {
    //         car.rotate(2);
    //     }
    // }

    // if (Collision::PixelPerfectTest(car.get_collision_sprite(),
    //                                 track.get_collision_sprite())) {
    //     car.accelerate(-0.5f);
    // }
    // car.update(0.02);

    // auto driver_position(car.get_position());
    // auto checking_point(driver_position);
    // std::cout << "Driver position: " << driver_position.x << ", " <<
    // driver_position.y
    //           << "\n";

    // const auto car_rotation = car.get_rotation();

    // while (checking_point.x > 0U && checking_point.x < image.getSize().x
    //        && checking_point.y > 0U && checking_point.y < image.getSize().y
    //        && image.getPixel(checking_point.x, checking_point.y)
    //               == sf::Color::Transparent) {

    //     checking_point.x += std::sin(car_rotation * to_rad_multiplier);
    //     checking_point.y -= std::cos(car_rotation * to_rad_multiplier);
    // }

    // const sf::Vertex line[] = {sf::Vertex(driver_position),
    //                            sf::Vertex(checking_point)};

    // std::cout << "Checking point: " << checking_point.x << ", " << checking_point.y
    //           << "\n";

    // const auto line_length =
    //     std::sqrt((driver_position.x - checking_point.x)
    //                   * (driver_position.x - checking_point.x)
    //               + (driver_position.y - checking_point.y)
    //                     * (driver_position.y - checking_point.y));
    // std::cout << "Length: " << line_length << " px\n";

    // track.draw_at(window);
    // car.draw_at(window);
    // window.draw(line, 2, sf::Lines);
}
