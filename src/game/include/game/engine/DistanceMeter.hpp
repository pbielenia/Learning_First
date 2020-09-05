#pragma once

#include "game/environment/Environment.hpp"
#include "helpers/Collision.hpp"
#include "helpers/math.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chrono>
#include <cmath>
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

    struct Lines {
        sf::VertexArray front{sf::Lines, 2};
        sf::VertexArray left{sf::Lines, 2};
        sf::VertexArray right{sf::Lines, 2};
        sf::VertexArray front_left{sf::Lines, 2};
        sf::VertexArray front_right{sf::Lines, 2};
    };

    struct Measures {
        Distances distances;
        Lines lines;
    };

    explicit DistanceMeter(const sf::Sprite& track)
        : track_limits{track.getTexture()->copyToImage()}
    {
    }

    Measures get_measures(const environment::Environment& environment)
    {
        create_lines(environment);
        calculate_distances();
        return std::move(measures);
    }

private:
    void create_lines(const environment::Environment& environment)
    {
        const auto driver_position{environment.car.model.position};
        const auto car_rotation{environment.car.model.rotation};

        auto front_endpoint = find_track_limit_at_line(driver_position, car_rotation);
        auto left_endpoint =
            find_track_limit_at_line(driver_position, car_rotation - 90.0F);
        auto right_endpoint =
            find_track_limit_at_line(driver_position, car_rotation + 90.0F);
        auto front_left_endpoint =
            find_track_limit_at_line(driver_position, car_rotation - 45.0F);
        auto front_right_endpoint =
            find_track_limit_at_line(driver_position, car_rotation + 45.0F);

        measures.lines.front.append(driver_position);
        measures.lines.front.append(front_endpoint);
        measures.lines.left.append(driver_position);
        measures.lines.left.append(left_endpoint);
        measures.lines.right.append(driver_position);
        measures.lines.right.append(right_endpoint);
        measures.lines.front_left.append(driver_position);
        measures.lines.front_left.append(front_left_endpoint);
        measures.lines.front_right.append(driver_position);
        measures.lines.front_right.append(front_right_endpoint);
    }

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

    void calculate_distances()
    {
        measures.distances.front = calculate_line_length(measures.lines.front);
        measures.distances.left = calculate_line_length(measures.lines.left);
        measures.distances.right = calculate_line_length(measures.lines.right);
        measures.distances.front_left = calculate_line_length(measures.lines.front_left);
        measures.distances.front_right = calculate_line_length(measures.lines.front_right);
    }

    float calculate_line_length(const sf::VertexArray& line)
    {
        return std::sqrt(std::pow(line[0].position.x - line[1].position.x, 2)
                         + std::pow(line[0].position.y - line[1].position.y, 2));
    }
    sf::Image track_limits;
    Measures measures;
};

} // namespace lf::game::engine
