#pragma once

#include <SFML/Graphics.hpp>

namespace lf::components {

struct Track {
    Track(const sf::Texture& texture_view) { sprite.setTexture(texture_view); }
    // drawing
    sf::Sprite sprite;
    // model
};

} // namespace lf::components
