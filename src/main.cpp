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

    User user{};

    std::string *array_words{ new std::string[2000]{} };

    TablaHash<Company*> companies{ 101 };
    GrafoSimple<Node*> company_network{ 22 };

    // Initialize store
    Store store{};

    try
    {
        initialize_anonymity(user.get_anonymity(), anonymity_sprite, anonymity_texture);
        initialize_map(texture_background, sprite_background);
        initialize_words(array_words);
        initialize_font(font);
        initialize_coins(user.get_yuca_coins(), font, coin_text, circle_coin_container, coin_texture);
        initialize_companies_and_network(companies, company_network);
        
        // Initialize store icon
        if (!store.initialize_store_icon()) {
            throw std::runtime_error("Failed to initialize store icon");
        }
        store.set_store_icon_position(26.f, 619.f);

        // Set positions for powers
        store.set_product_position("Exploit Enhancer", 610.f, 531.f);
        store.set_product_position("Firewall Bypass", 730.f, 468.f);
        store.set_product_position("Code Injection", 819.f, 408.f);
        store.set_product_position("Packet Sniffer", 819.f, 286.f);
        store.set_product_position("Rootkit Reducer", 661.f, 232.f);
        store.set_product_position("Malware Minimizer", 661.f, 334.f);
        store.set_product_position("DDoS Amplifier", 494.f, 468.f);
        store.set_product_position("Zero-Day Surge", 558.f, 334.f);
        store.set_product_position("Brute Force Multiplier", 557.f, 232.f);
        store.set_product_position("Ultimate Exploit", 407.f, 408.f);

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

    initialize_console_window(translucent_background, console, text_field);

    sf::Time countdown_time{ sf::seconds(120.0f) };
    sf::Clock countdown_clock{};

    Gameplay gameplay_status{};

    Cola<std::string> extracted_words{};
    std::string user_input{};
    std::string command_required{};

    sf::Clock console_time{};

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

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    store.handle_click(static_cast<float>(event.mouseButton.x), 
                                       static_cast<float>(event.mouseButton.y),
                                       font);
                }
                break;

            default:
                break;
            }
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
                std::cout << "\nCorrecto!\n";
                user_succeeds_attack(user, coin_text, company_network, companies, gameplay_status, company_index);
            }
            else
            {
                std::cout << "\nInorrecto!\n";
                user_fails_attack(user, anonymity_sprite, company_network, company_index);
            }

            clear_conditional_objects(extracted_words, click_flag, user_input, company_index);
        }

        window.clear(sf::Color::Black);
        window.draw(sprite_background);
        window.draw(anonymity_sprite);
        window.draw(circle_coin_container);
        window.draw(coin_text);

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

        if (click_flag && console_time.getElapsedTime().asSeconds() < 14.f && !store.is_store_open())
        {
            popup_console_window(user_input, command_required, command_required_text, input_command_text);
            window.draw(translucent_background);
            window.draw(console);
            window.draw(text_field);
            window.draw(command_required_text);
            window.draw(input_command_text);
        }
        else if (click_flag && !store.is_store_open())
        {
            user_fails_attack(user, anonymity_sprite, company_network, company_index);
            clear_conditional_objects(extracted_words, click_flag, user_input, company_index);
        }

        // Draw store
        store.draw(window, font);

        window.display();
    }

    //delete[] array_words;
    return 0;
}