#include "../include/configuration.hpp"
#include "../include/gui.hpp"
#include "../include/timmer.hpp"
#include "../include/company.hpp"
#include "../include/company_counter.hpp"
#include "../include/user.hpp"
#include "../include/actions.hpp"
#include "../include/puzzle.hpp"
#include "../include/estructuras/tabla_hash.hpp"
#include "../include/estructuras/grafo_simple.hpp"
#include "../include/estructuras/cola.hpp"
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

    std::string *array_words{ new std::string[2000]{} };

    try
    {
        initialize_map(texture_background, sprite_background);
        initialize_words(array_words);
        initialize_font(font);
    }
    catch (const std::runtime_error &error)
    {
        std::cerr << "Error in initialization. " << error.what();
        return 1;
    }

    sf::Text progress_bar_text{};
    sf::Text countdown_text{};
    sf::Text command_required_text{}; // palabras aleatorias
    sf::Text input_command_text{}; // input del usuario

    initialize_progress_bar_text(font, progress_bar_text);
    initialize_time_text(font, countdown_text);
    initialize_console_text(font, command_required_text);
    initialize_console_input_text(font, input_command_text);

    sf::RectangleShape translucent_background{ sf::Vector2f{ 1280.f, 720.f } };
    sf::RectangleShape console{ sf::Vector2f{640.f, 360.f} };
    sf::RectangleShape text_field{ sf::Vector2f{580.f, 50.f} };

    initialize_console_window(translucent_background, console, text_field);

    sf::Time countdown_time{ sf::seconds(120.0f) };
    sf::Clock countdown_clock{};

    TablaHash<Company*> companies{ 53 };
    GrafoSimple<sf::CircleShape*> company_network{ 22 };

    initialize_company_network(company_network);

    User user{};
    CompanyCounter company_counter{};

    Cola<std::string> extracted_words{};
    std::string user_input{};
    std::string command_required{};

    sf::Clock console_time{};

    bool click_flag{ false };
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

            case sf::Event::TextEntered:
                if (click_flag)
                {
                    // backspace (Tecla de borrar texto)
                    if (event.text.unicode == 8 && !user_input.empty())
                    {
                        user_input.pop_back(); // Eliminar el último carácter
                    }
                    else if (32 <= event.text.unicode && event.text.unicode <= 126)
                    {
                        // Esto es pa que sea ascii
                        user_input += static_cast<char>(event.text.unicode);
                    }
                }
                break;

            default:
                break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !click_flag)
        {
            verify_node_click(window, company_network, click_flag, console_time);

            if (click_flag)
            {
                command_required = get_command(6, extracted_words, array_words, true, true);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && click_flag)
        {
            std::cout << "Texto ingresado: " << user_input << '\n';
            std::cout << "Texto requerido: " << command_required << '\n';

            if (is_input_command_correct(user_input, extracted_words))
            {
                std::cout << "\nCorrecto!\n";
                // logica de correcto
            }
            else
            {
                std::cout << "\nInorrecto!\n";

                user.decrease_anonymity();
                if (user.was_captured())
                {
                    std::cout << "\nHA SIDO CAPTURADO BRO, RIP!!!11\n";
                    return 0;
                }
            }

            clear_extracted_words(extracted_words);
            click_flag = false;
            user_input = "";
        }

        window.clear(sf::Color::Black);
        window.draw(sprite_background);

        // For para dibujar los nodos de la compañia
        for (int i{0}; i < company_network.size(); ++i)
        {
            window.draw(*(company_network.get_element(i)));
        }

        draw_bar(window, progress_bar_text);
        draw_countdown(window, countdown_clock, countdown_time, countdown_text);

        if (click_flag && console_time.getElapsedTime().asSeconds() < 15.f)
        {
            popup_console_window(user_input, command_required, command_required_text, input_command_text);
            window.draw(translucent_background);
            window.draw(console);
            window.draw(text_field);
            window.draw(command_required_text);
            window.draw(input_command_text);
        }
        else if (click_flag)
        {
            clear_extracted_words(extracted_words);
            click_flag = false;
            user_input = "";
        }

        window.display();
    }

    return 0;
}