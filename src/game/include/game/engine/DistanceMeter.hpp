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
        sf::VertexArray left{sf::Lines, 2};
        sf::VertexArray right{sf::Lines, 2};
        sf::VertexArray front_left{sf::Lines, 2};
        sf::VertexArray front_right{sf::Lines, 2};
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

//        const sf::Vector2f versor_front{helpers::sin_deg(car_rotation),
//                                        helpers::cos_deg(car_rotation)};
//        const sf::Vector2f versor_left = rotate_vector(versor_front, -90.0F);

        auto front_endpoint = find_track_limit_at_line(driver_position, car_rotation);
        auto left_endpoint =
            find_track_limit_at_line(driver_position, car_rotation - 90.0F);
        auto right_endpoint =
            find_track_limit_at_line(driver_position, car_rotation + 90.0F);
        auto front_left_endpoint =
            find_track_limit_at_line(driver_position, car_rotation - 45.0F);
        auto front_right_endpoint =
            find_track_limit_at_line(driver_position, car_rotation + 45.0F);

        Lines lines;
        lines.front.append(driver_position);
        lines.front.append(front_endpoint);
        lines.left.append(driver_position);
        lines.left.append(left_endpoint);
        lines.right.append(driver_position);
        lines.right.append(right_endpoint);
        lines.front_left.append(driver_position);
        lines.front_left.append(front_left_endpoint);
        lines.front_right.append(driver_position);
        lines.front_right.append(front_right_endpoint);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " ms\n";
        return lines;
    }

private:
    sf::Vector2f rotate_vector(const sf::Vector2f& to_rotate, float angle)
    {
        return {to_rotate.x * helpers::cos_deg(angle)
                    - to_rotate.y * helpers::sin_deg(angle),
                to_rotate.x * helpers::sin_deg(angle)
                    + to_rotate.y * helpers::cos_deg(angle)};
    }

    sf::Vector2f find_track_limit_at_line(const sf::Vector2f& beginning, float line_slope)
    {
        auto endpoint{beginning};
        while (endpoint.x > 0U and endpoint.x < track_limits.getSize().x
               and endpoint.y > 0U and endpoint.y < track_limits.getSize().y
               and track_limits.getPixel(endpoint.x, endpoint.y)
                       == sf::Color::Transparent) {
            endpoint.x += (10.0F * helpers::sin_deg(line_slope));
            endpoint.y -= (10.0F * helpers::cos_deg(line_slope));
        }
        return endpoint;
    }

    sf::Image track_limits;
};

} // namespace lf::game::engine
