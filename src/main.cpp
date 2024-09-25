#include "../include/timmer.hpp"
#include "../include/configuration.hpp"
#include "../include/gui.hpp"
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
    sf::Text words_text{}; //palabras aleatorias
    sf::Text input_text{}; //input del usuario

    try
    {
        initialize_map(texture_background, sprite_background);
        initialize_progress_text(font, progress_bar_text);
        initialize_time_text(font, countdown_text);
        initialize_console_text(font, words_text);
        initialize_console_input_text(font, input_text);

    }
    catch (const std::runtime_error &error)
    {
        std::cerr << "Error in initialization. " << error.what();
        return 1;
    }

    sf::Time countdown_time{ sf::seconds(120.0f) };
    sf::Clock clock{};
    

    //Se crean y se meten 5 nodos en en un vector
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

            default:
                break;
            }

            if (event.type == sf::Event::TextEntered && click_flag) 
            {
                    //backspace
                if (event.text.unicode == 8 && !user_input.empty()) 
                {
                    user_input.pop_back(); // Eliminar el último carácter
                }

                else if (event.text.unicode < 128) 
                { //esto es pa que sea ascii
                    user_input += static_cast<char>(event.text.unicode);
                }
                
            }

        }

            
            
        


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            //Logica temporal para clickear los nodos de las compañias
            for (int i = 0; i < 5; ++i) {
                if (circles[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
                {
                    circles[i].setFillColor(sf::Color::Red);
                    std::cout << "Circle " << i + 1 << " clicked\n";
                    click_flag = true;
                    delay.restart();
                    
                }
            }
            
            
        }

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && click_flag)
        {
                std::cout << "Texto ingresado: " << user_input;
                click_flag = false;
                user_input = "";
        }

        
        window.clear(sf::Color::Black);
        window.draw(sprite_background);


        //For para dibujar los nodos de la compañia
        for (int i = 0; i < circles.size(); ++i) {
            window.draw(circles[i]);
        }


        draw_bar(window, progress_bar_text);
        draw_countdown(window, clock, countdown_time, countdown_text);

        if (click_flag && delay.getElapsedTime().asSeconds() < 10.f)
        {

            popup_window(window, words_text, input_text, user_input);

        }
        else
        {
            user_input = "";
        }

        window.display();

    }

    return 0;
}