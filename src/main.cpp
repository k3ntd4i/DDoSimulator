#include "../include/configuration.hpp"
#include "../include/gui.hpp"
#include "../include/timmer.hpp"
#include "../include/company.hpp"
#include "../include/node.hpp"
#include "../include/gameplay.hpp"
#include "../include/user.hpp"
#include "../include/actions.hpp"
#include "../include/puzzle.hpp"
#include "../include/estructuras/tabla_hash.hpp"
#include "../include/estructuras/grafo_simple.hpp"
#include "../include/estructuras/cola.hpp"
#include "../include/store.hpp"
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

    sf::Texture coin_texture{};
    sf::CircleShape circle_coin_container{};

    sf::Texture anonymity_texture{};
    sf::Sprite anonymity_sprite{};
    sf::Font font{};

    sf::Text coin_text{};

    sf::Texture fail_background_texture{};
    sf::Sprite fail_background_sprite{};
    sf::Text fail_text{};

    sf::Texture win_background_texture{};
    sf::Sprite win_background_sprite{};
    sf::Text win_text{};

    sf::Text exit_text{};

    User user{};

    std::string *array_words{ new std::string[2000]{} };

    TablaHash<Company*> companies{ 101 };
    GrafoSimple<Node*> company_network{ 22 };

    Store store{};

    try
    {
        initialize_anonymity(user.get_anonymity(), anonymity_sprite, anonymity_texture);
        initialize_map(texture_background, sprite_background);
        initialize_words(array_words);
        initialize_font(font);
        initialize_coins(user.get_yuca_coins(), font, coin_text, circle_coin_container, coin_texture);
        initialize_companies_and_network(companies, company_network);
        store.initialize_store_icon();
        initialize_fail_background(fail_background_texture, fail_background_sprite, font, fail_text);
        initialize_win_background(win_background_texture, win_background_sprite, font, win_text);
    }
    catch (const std::runtime_error &error)
    {
        std::cerr << "Error in initialization. " << error.what();
        return 1;
    }

    sf::Text progress_bar_text{};
    sf::Text countdown_text{};
    sf::Text command_required_text{}; // palabras aleatorias
    sf::Text input_command_text{}; // input del usuario en la consola

    initialize_progress_bar_text(font, progress_bar_text);
    initialize_time_text(font, countdown_text);
    initialize_console_text(font, command_required_text);
    initialize_console_input_text(font, input_command_text);

    sf::RectangleShape translucent_background{ sf::Vector2f{ 1280.f, 720.f } };
    sf::RectangleShape console{ sf::Vector2f{ 640.f, 360.f } };
    sf::RectangleShape text_field{ sf::Vector2f{ 580.f, 50.f } };
    sf::RectangleShape time_bar{ sf::Vector2f{ 638.f, 10.f } };

    initialize_console_window(translucent_background, console, text_field);

    sf::Time countdown_time{ sf::seconds(200.0f) };
    sf::Clock countdown_clock{};

    Gameplay gameplay_status{};

    Cola<std::string> extracted_words{};
    std::string user_input{};
    std::string command_required{};

    sf::Clock console_time{};
    sf::Clock console_time_indicator{}; //para la barra de tiempo xd

    bool end_game{ false };
    bool click_flag{ false };
    int company_index{};
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
                    // Backspace (Tecla de borrar texto)
                    if (event.text.unicode == 8 && !user_input.empty())
                    {
                        user_input.pop_back(); // Eliminar el último carácter
                    }
                    else if (32 <= event.text.unicode && event.text.unicode <= 126)
                    {
                        // Pasar de unicode a ASCII
                        user_input += static_cast<char>(event.text.unicode);
                    }
                }
                break;

            default:
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && end_game)
        {
            window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !click_flag && !store.is_store_open())
        {
            verify_node_click(window, company_network, click_flag, console_time, company_index);

            if (click_flag)
            {
                command_required = get_command
                (
                    gameplay_status.get_quantity_words(),
                    extracted_words,
                    array_words,
                    gameplay_status.get_hard(),
                    gameplay_status.get_extreme()
                );
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && click_flag)
        {
            std::cout << "Texto ingresado: " << user_input << '\n';
            std::cout << "Texto requerido: " << command_required << '\n';

            if (is_input_command_correct(user_input, extracted_words))
            {
                std::cout << "Correcto!\n";
                user_succeeds_attack(user, coin_text, company_network, companies, gameplay_status, company_index);
            }
            else
            {
                std::cout << "Inorrecto!\n";
                user_fails_attack(user, anonymity_sprite, company_network, company_index);
            }

            clear_conditional_objects(extracted_words, click_flag, user_input, company_index);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !click_flag)
        {
            store.handle_click
            (
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y),
                coin_text,
                user,
                gameplay_status
            );
        }

        window.clear(sf::Color::Black);
        window.draw(sprite_background);
        window.draw(anonymity_sprite);

        // For para dibujar los nodos
        for (int i{0}; i < company_network.size(); ++i)
        {
            Node *temporal_node{ company_network.get_element(i) };

            if (temporal_node->was_just_attacked())
            {
                if (temporal_node->is_infected())
                {
                    temporal_node->get_circle().setOutlineThickness(0.f);
                    temporal_node->get_circle().setFillColor(sf::Color::Green);
                    temporal_node->set_status_available(false);
                    temporal_node->set_was_just_attacked(false);
                }
                else if (temporal_node->get_elapsed_seconds() >= 5.f)
                {
                    temporal_node->get_circle().setFillColor(sf::Color::White);
                    temporal_node->get_circle().setOutlineColor(sf::Color::White);
                    temporal_node->set_status_available(true);
                    temporal_node->set_was_just_attacked(false);
                }
            }

            window.draw(company_network.get_element(i)->get_circle());
        }

        draw_bar(window, progress_bar_text, gameplay_status);
        draw_countdown(window, countdown_clock, countdown_time, countdown_text);
        store.draw(window, font, user);
        window.draw(circle_coin_container);
        window.draw(coin_text);

        if (click_flag && console_time.getElapsedTime().asSeconds() < 14.f && !store.is_store_open())
        {
            popup_console_window(user_input, command_required, command_required_text, input_command_text,
            console_time, time_bar);
            window.draw(translucent_background);
            window.draw(console);
            window.draw(text_field);
            window.draw(command_required_text);
            window.draw(input_command_text);
            window.draw(time_bar);
        }
        else if (click_flag && !store.is_store_open())
        {
            user_fails_attack(user, anonymity_sprite, company_network, company_index);
            clear_conditional_objects(extracted_words, click_flag, user_input, company_index);
        }

        if (user.get_anonymity() == 0 || countdown_clock.getElapsedTime().asSeconds() >= 200.f)
        {
            end_game = true;
            window.draw(fail_background_sprite);
            window.draw(fail_text);
            sf::Mouse::setPosition(sf::Vector2i{640, 360}, window);
        }
        else if (gameplay_status.get_company_counter() == 22)
        {
            end_game = true;
            window.draw(win_background_sprite);
            window.draw(win_text);
            sf::Mouse::setPosition(sf::Vector2i{640, 360}, window);
        }

        window.display();
    }

    return 0;
}