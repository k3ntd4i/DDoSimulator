#include "../include/configuration.hpp"
#include "../include/store.hpp"
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

    Store store{};

    try
    {
        initialize_map(texture_background, sprite_background);
        initialize_words(array_words);
        if (!store.initialize_store_icon()) {
            throw std::runtime_error{ "Failed to load store icon." };
        }
        store.set_store_icon_position(10.f, window.getSize().y - 60.f);
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
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    store.handle_click(event.mouseButton.x, event.mouseButton.y);
                }
                break;
            default:
                break;
            }
        }

        store.update(window);

        window.clear(sf::Color::Black);
        window.draw(sprite_background);
        store.draw(window);
        window.display();
    }

    delete[] array_words;
    return 0;
}