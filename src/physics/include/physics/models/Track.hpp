#pragma once

#include <SFML/Graphics.hpp>

namespace lf::physics::models {

struct Track {
    Track(const sf::Texture& texture) : sprite{texture} {}

    sf::Sprite sprite;
};

} // namespace lf::physics::models
