#pragma once

#include "physics/models/Vehicle.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

namespace lf::game::environment {

struct Car {

    struct TexturesPack {
        TexturesPack(const sf::Texture& drawing,
                     const sf::Texture& wheels,
                     float scale = 1.0F)
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
        float wheels_angle{0.0F};
    };

    Car(const TexturesPack& textures, const TechnicalSpecs& technical_specs)
        : drawing{textures.drawing}, model{technical_specs.max_acceleration,
                                           technical_specs.max_speed,
                                           textures.wheels,
                                           textures.scale}

    {
        drawing.setScale(textures.scale, textures.scale);

        const auto dimensions = drawing.getLocalBounds();
        const auto center_x = dimensions.width / 2.0F;
        const auto center_y = dimensions.height / 2.0F;
        drawing.setOrigin(center_x, center_y);
        model.wheels.setOrigin(center_x, center_y);
    }

    void set_position(float x, float y)
    {
        model.position.x = x;
        model.position.y = y;
        model.wheels.setPosition(x, y);
    }

    void set_rotation(float degrees) { model.rotation = degrees; }

    void update_drawing()
    {
        drawing.setPosition(model.position);
        drawing.setRotation(model.rotation);
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
