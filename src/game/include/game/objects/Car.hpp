#pragma once

#include "physics/models/Vehicle.hpp"

#include <SFML/Graphics.hpp>

namespace lf::game::objects {

struct Car {

    struct TexturesPack {
        TexturesPack(const sf::Texture& drawing,
                     const sf::Texture& wheels,
                     float scale = 1.0f)
            : drawing{drawing}, wheels{wheels}, scale{scale}
        {
        }

        const sf::Texture& drawing;
        const sf::Texture& wheels;
        float scale;
    };

    struct TechnicalSpecs {
        unsigned max_speed{0U};
        unsigned max_acceleration{0U};
    };

    struct Steering {
        bool accelerating{false};
        bool braking{false};
        float wheels_angle{0.0f};
    };

    Car(const TexturesPack& textures, const TechnicalSpecs& technical_specs)
        : drawing{textures.drawing}, model{technical_specs.max_acceleration,
                                           technical_specs.max_speed,
                                           textures.wheels,
                                           textures.scale}

    {
        drawing.setScale(textures.scale, textures.scale);
    }

    void set_steering(const Steering& steering)
    {
        model.accelerating = steering.accelerating;
        model.braking = steering.braking;
        model.wheels_angle = steering.wheels_angle;
    }

    sf::Sprite drawing;
    physics::models::Vehicle model;
};

} // namespace lf::game::objects
