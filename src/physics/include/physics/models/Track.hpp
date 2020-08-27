#pragma once

#include <SFML/Graphics.hpp>

namespace lf::physics::models {

struct Track {
    Track(const sf::Texture& limits, float scale = 1.0f) : limits{limits}
    {
        this->limits.setScale(scale, scale);
    }

    sf::Sprite limits;
};

} // namespace lf::physics::models
