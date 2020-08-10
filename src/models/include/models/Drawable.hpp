#pragma once

#include <SFML/Graphics.hpp>

namespace lf::models {
class Drawable {
public:
    Drawable(const sf::Texture& texture, float scale = 1.0f)
    {
        set_texture(texture);
        set_scale(scale);
    }

    void draw_at(sf::RenderWindow& window);

protected:
    void set_texture(const sf::Texture& texture);
    void set_scale(float scale);
    void set_origin(const sf::Vector2f coords);
    void set_position(float x, float y);
    void set_rotation(float angle);
    sf::Vector2f get_middle() const;
    void move(const sf::Vector2f& translation_vector);
    void rotate(float rotation);

private:
    sf::Sprite sprite;
};
} // namespace lf::models
