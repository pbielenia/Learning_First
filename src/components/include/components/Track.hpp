#pragma once

#include "physics/models/Track.hpp"

#include <SFML/Graphics.hpp>

namespace lf::components {

struct Track {
    Track(const sf::Texture& texture_view, const sf::Texture& texture_collisions)
        : sprite{texture_view}, model{texture_collisions}
    {
    }
    // drawing
    sf::Sprite sprite;
    // model
    physics::models::Track model;
};

} // namespace lf::components
