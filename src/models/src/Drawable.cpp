#include "Drawable.hpp"

using namespace lf::models;

void Drawable::draw_at(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Drawable::set_texture(const sf::Texture& texture)
{
    sprite.setTexture(texture);
}

void Drawable::set_scale(float scale)
{
    sprite.setScale(scale, scale);
}

void Drawable::set_origin(const sf::Vector2f coords)
{
    sprite.setOrigin(coords);
}

void Drawable::set_position(float x, float y)
{
    sprite.setPosition(x, y);
}

void Drawable::set_rotation(float angle)
{
    sprite.setRotation(angle);
}

sf::Vector2f Drawable::get_middle() const
{
    const auto local_bound = sprite.getLocalBounds();
    return {local_bound.width / 2.0f, local_bound.height / 2.0f};
}

void Drawable::move(const sf::Vector2f& translation_vector)
{
    sprite.move(translation_vector);
}

void Drawable::rotate(float rotation)
{
    sprite.rotate(rotation);
}
