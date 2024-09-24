#include "../include/configuration.hpp"

void initialize_window(sf::RenderWindow &window, sf::View &view)
{
    unsigned int pixel_depth{ sf::VideoMode::getDesktopMode().bitsPerPixel };

    window.create(sf::VideoMode{ 1280, 720, pixel_depth }, "DDoSimulator");
    view.reset(sf::FloatRect{ 0.f, 0.f, 1280.f, 720.f });

    window.setVerticalSyncEnabled(true);
    window.setView(view);
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
