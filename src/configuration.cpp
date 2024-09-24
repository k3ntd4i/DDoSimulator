#include "../include/configuration.hpp"

void initialize_window(sf::RenderWindow &window)
{
    window.create
    (
        sf::VideoMode{ 1280, 720, sf::VideoMode::getDesktopMode().bitsPerPixel },
        "DDoSimulator"
    );

    window.setVerticalSyncEnabled(true);
}

void initialize_map(sf::Texture &texture_background, sf::Sprite &sprite_background)
{
    if (!texture_background.loadFromFile(R"(assets\images\map.png)"))
    {
        throw std::runtime_error{ "The background could not be loaded." };
    }

    sprite_background.setTexture(texture_background);
    sprite_background.setScale(0.26f, 0.26f);
    sprite_background.setPosition(112.f, 76.f);
}
