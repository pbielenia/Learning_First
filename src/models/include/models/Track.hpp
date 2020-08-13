#pragma once

#include "Drawable.hpp"

namespace lf::models {

class Track : public Drawable {
public:
    Track(const sf::Texture& texture_view, const sf::Texture& texture_collision)
        : Drawable{texture_view, texture_collision}
    {
    }

private:
    //
};

} // namespace lf::models
