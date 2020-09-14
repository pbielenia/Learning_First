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
        Distances() = default;

        Distances(
            float front, float left, float front_left, float right, float front_right)
            : front{front}, left{left}, front_left{front_left}, right{right},
              front_right{front_right}
        {
        }

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

    enum class Segment { None, First, Second, Third };

    struct Measures {
        Distances distances;
        Lines lines;
        Segment segment;
        bool out_of_track{false};
    };

    explicit DistanceMeter(const sf::Sprite& track)
        : track_limits{track.getTexture()->copyToImage()}
    {
    }

    Measures get_measures(const environment::Environment& environment)
    {
        create_lines(environment);
        calculate_distances();
        check_segments(environment);
        check_out_of_track(environment);
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
        static const auto grass_color = sf::Color(47, 167, 32, 255);
        auto endpoint{beginning};
        while (endpoint.x > 0U and endpoint.x < track_limits.getSize().x
               and endpoint.y > 0U and endpoint.y < track_limits.getSize().y
               and track_limits.getPixel(endpoint.x, endpoint.y) != grass_color) {
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
        measures.distances.front_right =
            calculate_line_length(measures.lines.front_right);
    }

    float calculate_line_length(const sf::VertexArray& line)
    {
        return std::sqrt(std::pow(line[0].position.x - line[1].position.x, 2)
                         + std::pow(line[0].position.y - line[1].position.y, 2));
    }

    void check_segments(const environment::Environment& environment)
    {
        static const auto segment_a_color = sf::Color(167, 144, 32, 255);
        static const auto segment_b_color = sf::Color(214, 220, 60, 255);
        static const auto segment_c_color = sf::Color(171, 211, 31, 255);

        const auto& car_position = environment.car.model.position;
        const auto car_pixel_color =
            track_limits.getPixel(car_position.x, car_position.y);

        if (car_pixel_color == segment_a_color) {
            measures.segment = Segment::First;
        } else if (car_pixel_color == segment_b_color) {
            measures.segment = Segment::Second;
        } else if (car_pixel_color == segment_c_color) {
            measures.segment = Segment::Third;
        } else {
            measures.segment = Segment::None;
        }
    }

    void check_out_of_track(const environment::Environment& environment)
    {
        static const auto grass_color = sf::Color(47, 167, 32, 255);

        const auto& car_position = environment.car.model.position;
        const auto car_pixel = track_limits.getPixel(car_position.x, car_position.y);

        if (car_pixel == grass_color) {
            measures.out_of_track = true;
        } else {
            measures.out_of_track = false;
        }
    }

    sf::Image track_limits;
    Measures measures;
};

static bool operator==(const DistanceMeter::Distances& lhs,
                       const DistanceMeter::Distances& rhs)
{
    return std::tuple(lhs.right, lhs.front_right, lhs.front, lhs.front_left, lhs.left)
           == std::tuple(rhs.right, rhs.front_right, rhs.front, rhs.front_left, rhs.left);
}

static bool operator<(const DistanceMeter::Distances& lhs,
                      const DistanceMeter::Distances& rhs)
{
    return std::tuple(lhs.right, lhs.front_right, lhs.front, lhs.front_left, lhs.left)
           < std::tuple(rhs.right, rhs.front_right, rhs.front, rhs.front_left, rhs.left);
}

} // namespace lf::game::engine
