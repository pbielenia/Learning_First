#pragma once

#include "Drawable.hpp"

namespace lf::models {

class Track : public Drawable {
public:
    Track(const sf::Texture& texture) : Drawable{texture} {}

private:
    //
};

} // namespace lf::models
