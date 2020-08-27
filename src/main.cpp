
#include "game/engine/Core.hpp"
#include "game/engine/TexturesLoader.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    std::cout << "Learning First start\n";
    lf::game::engine::TexturesLoader textures_loader{"images"};
    textures_loader.load();
    if (textures_loader.has_texture("car.png")) {
        const auto car_tex = textures_loader.get_texture("car.png");
    }

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
