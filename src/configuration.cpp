#include "../include/configuration.hpp"

void initialize_window(sf::RenderWindow &window, sf::View &view)
{
    unsigned int pixel_depth{ sf::VideoMode::getDesktopMode().bitsPerPixel };

    window.create(sf::VideoMode{ 800, 600, pixel_depth }, "DDoSimulator");
    view.reset(sf::FloatRect{ 0.f, 0.f, 800.f, 600.f });

    window.setVerticalSyncEnabled(true);
    window.setView(view);
}
