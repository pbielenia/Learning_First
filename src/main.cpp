#include "game/engine/Engine.hpp"
#include "game/engine/TexturesLoader.hpp"
#include "game/environment/Environment.hpp"

#include <SFML/Graphics.hpp>
#include <game/driver/KeyboardInput.hpp>
#include "game/driver/Bot.hpp"
#include <iostream>

lf::game::environment::Car
create_car_object(const lf::game::engine::TexturesLoader& textures_loader)
{
    try {
        lf::game::environment::Car::TexturesPack textures{
            textures_loader.get_texture("car.png"),
            textures_loader.get_texture("car-wheels.png"),
            0.1f};
        lf::game::environment::Car::TechnicalSpecs technical_specs;
        technical_specs.max_speed = 3;
        technical_specs.max_acceleration = 3;

        return {textures, technical_specs};

    } catch (const std::exception& e) {
        throw std::runtime_error("Creating a car object has failed due to: "
                                 + std::string(e.what()));
    }
}

lf::game::environment::Track
create_track_object(const lf::game::engine::TexturesLoader& textures_loader)
{
    try {
        lf::game::environment::Track::TexturesPack textures{
            textures_loader.get_texture("custom_track.png"),
            textures_loader.get_texture("custom_track-meta.png")};

        return {textures};

    } catch (const std::exception& e) {
        throw std::runtime_error("Creating a track object has failed due to: "
                                 + std::string(e.what()));
    }
}

int main()
{
    std::cout << "Learning First start\n";
    lf::game::engine::TexturesLoader textures_loader{"images"};
    textures_loader.load();
    auto car = create_car_object(textures_loader);
    car.set_position(600.0f, 100.0f);
    car.set_rotation(90.0f);
    auto track = create_track_object(textures_loader);

    lf::game::environment::Environment environment{std::move(car), std::move(track)};
    lf::game::engine::Engine game{std::move(environment)};
//    auto driver = lf::game::driver::KeyboardInput::create(game.get_event());
    auto driver = lf::game::driver::Bot::create();
    game.set_driver(std::move(driver));
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
