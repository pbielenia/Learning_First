#pragma once

#include "helpers/Collision.hpp"

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <map>
#include <optional>
#include <string>

namespace lf::game::engine {

class TexturesLoader {
public:
    TexturesLoader(const std::string& path) : path{path} {}
    void load()
    {
        for (const auto& file : std::filesystem::directory_iterator(path)) {
            if (file.is_regular_file() && file.path().extension() == ".png") {
                sf::Texture texture;
                if (Collision::CreateTextureAndBitmask(texture, file.path()) == true) {
                    std::cout << "Read texture from file " << file.path().filename()
                              << " of size " << texture.getSize().x << "x"
                              << texture.getSize().y << " px.\n";
                    textures.emplace(file.path().filename(), std::move(texture));
                } else {
                    std::cout << "Reading texture from file " << file.path().filename()
                              << " has failed.\n";
                }
            }
        }
    }

private:
    std::optional<sf::Texture> read_texture(const std::string& path)
    {
        sf::Texture texture;
        if (Collision::CreateTextureAndBitmask(texture, path) == false) {
            return {};
        } else {
            return texture;
        }
    }

    std::string path;
    std::map<std::filesystem::path, sf::Texture> textures;
};

} // namespace lf::game::engine
