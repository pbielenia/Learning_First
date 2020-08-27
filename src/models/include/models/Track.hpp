#pragma once

#include "Drawable.hpp"
#include "Vehicle.hpp"

#include <memory>
#include <vector>

namespace lf::models {

class Track : public Drawable {
public:
    Track(const sf::Texture& texture_view, const sf::Texture& texture_collision)
        : Drawable{texture_view, texture_collision}
    {
    }

    void put_vehicle(std::unique_ptr<Vehicle> vehicle);

private:
    std::vector<std::unique_ptr<Vehicle>> vehicles_on;
};

} // namespace lf::models
