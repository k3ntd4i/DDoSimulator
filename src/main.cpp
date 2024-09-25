#include "../include/timmer.hpp"
#include "../include/configuration.hpp"
#include "../include/gui.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <stdexcept>
#include <iostream>
#include <string>

int main()
{
    sf::RenderWindow window{};
    initialize_window(window);

    sf::Texture texture_background{};
    sf::Sprite sprite_background{};
    
    sf::Font font{};
    sf::Text progress_bar_text{};
    sf::Text countdown_text{};

    std::string *array_words{ new std::string[2000]{} };

    try
    {
        initialize_map(texture_background, sprite_background);
        initialize_progress_text(font, progress_bar_text);
        initialize_time_text(font, countdown_text);
        initialize_words(array_words);
    }
    catch (const std::runtime_error &error)
    {
        std::cerr << "Error in initialization. " << error.what();
        return 1;
    }

    sf::Time countdown_time{ sf::seconds(120.0f) };
    sf::Clock clock{};

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

        draw_bar(window, progress_bar_text);
        draw_countdown(window, clock, countdown_time, countdown_text);

        window.display();
    }

    return 0;
}