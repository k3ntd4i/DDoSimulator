#include "../include/configuration.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <stdexcept>
#include <iostream>

int main()
{
    sf::RenderWindow window{};
    sf::View view{};

    sf::Texture texture_background{};
    sf::Sprite sprite_background{};

    initialize_window(window, view);
    try
    {
        initialize_map(texture_background, sprite_background);
    }
    catch (const std::runtime_error &error)
    {
        std::cerr << "Error in initialization. " << error.what();
        return 1;
    }

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(sprite_background);
        window.display();
    }

    return 0;
}