#pragma once

#include "physics/models/Track.hpp"

#include <SFML/Graphics.hpp>

namespace lf::game::environment {

struct Track {

    struct TexturesPack {
        TexturesPack(const sf::Texture& drawing,
                     const sf::Texture& limits,
                     float scale = 1.0f)
            : drawing{drawing}, limits{limits}, scale{scale}
        {
        }

        const sf::Texture& drawing;
        const sf::Texture& limits;
        float scale;
    };

    Track(const TexturesPack& textures)
        : drawing{textures.drawing}, model{textures.limits, textures.scale}
    {
        drawing.setScale(textures.scale, textures.scale);
    }

    sf::Sprite drawing;
    physics::models::Track model;
};

} // namespace lf::game::objects
