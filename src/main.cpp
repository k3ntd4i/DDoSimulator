#include "../include/timmer.hpp"
#include "../include/configuration.hpp"
#include "../include/gui.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <stdexcept>
#include <iostream>

int main()
{
    

    sf::RenderWindow window{};
    initialize_window(window);

    sf::Texture texture_background{};
    sf::Sprite sprite_background{};
    
    sf::Font font{};
    sf::Text text{};
    sf::Text countdown_text;

    sf::Time countdown_time{sf::seconds(120.0f)};
    sf::Clock clock{};
    


    try
    {
        initialize_map(texture_background, sprite_background);
        initialize_text(font, text);
        initialize_time_text(font, countdown_text);
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

        draw_bar(window, text);
        draw_countdown(window, clock, countdown_time, countdown_text);

        window.display();

    }

    return 0;
}