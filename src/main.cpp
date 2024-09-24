#include "../include/configuration.hpp"
#include "../include/puzzle.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <stdexcept>
#include <iostream>
#include <string>

int main()
{
    sf::RenderWindow window{};
    initialize_window(window);

    sf::Texture texture_background{};
    sf::Sprite sprite_background{};

    std::string *array_words{ new std::string[2000]{} };

    try
    {
        initialize_map(texture_background, sprite_background);
        initialize_words(array_words);
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