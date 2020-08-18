#pragma once

#include "collisions/Collision.hpp"

#include <SFML/Graphics.hpp>

namespace lf::models {
class Drawable {
public:
    Drawable(const sf::Texture& texture_view,
             const sf::Texture& texture_collision,
             float scale = 1.0f)
    {
        set_textures(texture_view, texture_collision);
        set_scale(scale);
    }

    void draw_at(sf::RenderWindow& window);
    const sf::Sprite& get_collision_sprite() const;

protected:
    void set_textures(const sf::Texture& texture_view,
                      const sf::Texture& texture_collision);
    void set_scale(float scale);
    void set_origin(const sf::Vector2f coords);
    void set_position(float x, float y);
    void set_rotation(float angle);
    sf::Vector2f get_middle() const;
    sf::Vector2f get_position() const;
    float get_rotation() const;
    void move(const sf::Vector2f& translation_vector);
    void rotate(float rotation);

private:
    sf::Sprite sprite_view;
    sf::Sprite sprite_collision;
};
} // namespace lf::models
