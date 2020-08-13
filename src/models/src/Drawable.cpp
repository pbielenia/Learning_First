#include "Drawable.hpp"

using namespace lf::models;

void Drawable::draw_at(sf::RenderWindow& window)
{
    window.draw(sprite_view);
}

const sf::Sprite& Drawable::get_collision_sprite() const
{
    return sprite_collision;
}

void Drawable::set_textures(const sf::Texture& texture_view,
                            const sf::Texture& texture_collision)
{
    sprite_view.setTexture(texture_view);
    sprite_collision.setTexture(texture_collision);
}

void Drawable::set_scale(float scale)
{
    sprite_view.setScale(scale, scale);
    sprite_collision.setScale(scale, scale);
}

void Drawable::set_origin(const sf::Vector2f coords)
{
    sprite_view.setOrigin(coords);
    sprite_collision.setOrigin(coords);
}

void Drawable::set_position(float x, float y)
{
    sprite_view.setPosition(x, y);
    sprite_collision.setPosition(x, y);
}

void Drawable::set_rotation(float angle)
{
    sprite_view.setRotation(angle);
    sprite_collision.setRotation(angle);
}

sf::Vector2f Drawable::get_middle() const
{
    const auto local_bound = sprite_view.getLocalBounds();
    return {local_bound.width / 2.0f, local_bound.height / 2.0f};
}

void Drawable::move(const sf::Vector2f& translation_vector)
{
    sprite_view.move(translation_vector);
    sprite_collision.move(translation_vector);
}

void Drawable::rotate(float rotation)
{
    sprite_view.rotate(rotation);
    sprite_collision.rotate(rotation);
}
