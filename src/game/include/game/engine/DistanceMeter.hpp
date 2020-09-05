#pragma once

#include "game/environment/Environment.hpp"
#include "helpers/Collision.hpp"
#include "helpers/math.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chrono>
#include <iostream>

namespace lf::game::engine {

class DistanceMeter {
public:
    struct Distances {
        float front{0.0F};
        float left{0.0F};
        float front_left{0.0F};
        float right{0.0F};
        float front_right{0.0F};
    };
    //
    struct Lines {
        sf::VertexArray front{sf::Lines, 2};
        //        std::pair<sf::Vector2f, sf::Vector2f> left{{0.0F, 0.0F}, {0.0F, 0.0F}};
        //        sf::Vector2f front_left{0.0F, 0.0F};
        //        sf::Vector2f right{0.0F, 0.0F};
        //        sf::Vector2f front_right{0.0F, 0.0F};
    };

    explicit DistanceMeter(const sf::Sprite& track)
        : track_limits{track.getTexture()->copyToImage()}
    {
    }

    Lines get_lines(const environment::Environment& environment)
    {
        auto start = std::chrono::high_resolution_clock::now();

        const auto driver_position{environment.car.model.position};
        const auto car_rotation{environment.car.model.rotation};
        //        std::cout << driver_position.x << ", " << driver_position.y << ", "
        //                  << car_rotation << "\n";

        const sf::Vector2f versor_front{helpers::sin_deg(car_rotation),
                                        helpers::cos_deg(car_rotation)};

        const auto image_load_time = std::chrono::high_resolution_clock::now();

        auto checking_point{driver_position};
        while (checking_point.x > 0U and checking_point.x < track_limits.getSize().x
               and checking_point.y > 0U and checking_point.y < track_limits.getSize().y
               and track_limits.getPixel(checking_point.x, checking_point.y)
                       == sf::Color::Transparent) {
            checking_point.x += (10.0F * helpers::sin_deg(car_rotation));
            checking_point.y -= (10.0F * helpers::cos_deg(car_rotation));
        }

        Lines lines;
        lines.front.append(driver_position);
        lines.front.append(checking_point);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout
            << "image: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(image_load_time
                                                                     - start)
                   .count()
            << " ms, full: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " ms\n";
        return lines;
    }

private:
    sf::Image track_limits;
};

} // namespace lf::game::engine
