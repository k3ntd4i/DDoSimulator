#include "../include/timmer.hpp"
#include "../include/configuration.hpp"
#include "../include/gui.hpp"
#include "../include/store.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>

int main()
{
    sf::RenderWindow window{};
    initialize_window(window);

    sf::Texture texture_background{};
    sf::Sprite sprite_background{};
    
    sf::Font font{};
    sf::Text progress_bar_text{};
    sf::Text countdown_text{};
    sf::Text words_text{}; // palabras aleatorias
    sf::Text input_text{}; // input del usuario

    Store store{};

    try
    {
        initialize_map(texture_background, sprite_background);
        initialize_progress_text(font, progress_bar_text);
        initialize_time_text(font, countdown_text);
        initialize_console_text(font, words_text);
        initialize_console_input_text(font, input_text);
        store.initialize_store_icon();
    }
    catch (const std::runtime_error &error)
    {
        std::cerr << "Error in initialization. " << error.what();
        return 1;
    }

    sf::Time countdown_time{ sf::seconds(120.0f) };  // Tiempo inicial
    sf::Clock clock{};  // Reloj del juego
    sf::Time paused_time{};  // Tiempo acumulado al abrir la tienda
    bool store_opened_last_frame = false;  // Para saber si la tienda se abrió o cerró

    std::vector<sf::CircleShape> circles(5);
    
    for (int i = 0; i < 5; ++i) {
        circles[i].setRadius(50); 
        circles[i].setPosition(100 * (i + 5), 200); 
        circles[i].setFillColor(sf::Color::Green);
    }

    std::string user_input{""};
    sf::Clock delay{};

    bool click_flag{false};

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
                if (event.mouseButton.button == sf::Mouse::Left) {
                    store.handle_click(static_cast<float>(sf::Mouse::getPosition(window).x), 
                                       static_cast<float>(sf::Mouse::getPosition(window).y));
                }
                break;
            case sf::Event::TextEntered:
                if (click_flag) {
                    if (event.text.unicode == 8 && !user_input.empty()) {
                        user_input.pop_back();
                    } else if (event.text.unicode < 128) {
                        user_input += static_cast<char>(event.text.unicode);
                    }
                }
                break;
            default:
                break;
            }
        }

        // Control del tiempo basado en la tienda abierta o cerrada
        if (store.is_store_open()) {
            if (!store_opened_last_frame) {
                // Tienda acaba de abrirse, guardar el tiempo transcurrido y pausar el reloj
                paused_time = countdown_time;  // Guardamos el tiempo actual del countdown
            }
            // Mientras la tienda esté abierta, no actualizamos el tiempo (queda en pausa)
        } else {
            if (store_opened_last_frame) {
                // Tienda acaba de cerrarse, reiniciar el reloj y retomar desde donde estaba el tiempo
                countdown_time = paused_time;  // Restauramos el tiempo pausado
                clock.restart();  // Reiniciamos el reloj para que comience desde aquí
            } else {
                // Mientras la tienda esté cerrada, el tiempo avanza normalmente
                countdown_time -= clock.restart();  // Actualizar el tiempo transcurrido
            }
        }

        store_opened_last_frame = store.is_store_open();  // Actualizamos el estado de la tienda

        window.clear(sf::Color::Black);
        window.draw(sprite_background);

        for (int i = 0; i < circles.size(); ++i) {
            window.draw(circles[i]);
        }

        draw_bar(window, progress_bar_text);
        
        // Dibujar el temporizador solo si la tienda está cerrada
        if (!store.is_store_open()) {
            draw_countdown(window, clock, countdown_time, countdown_text);
        }

        if (click_flag && delay.getElapsedTime().asSeconds() < 10.f) {
            popup_window(window, words_text, input_text, user_input);
        } else {
            user_input = "";
        }

        store.draw(window);
        window.display();
    }

    return 0;
}
