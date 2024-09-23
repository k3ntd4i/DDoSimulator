#include "../include/configuration.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

int main()
{
    sf::RenderWindow window{};
    sf::View view{};

    initialize_window(window, view);

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
        window.display();
    }

    return 0;
}