#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "../include/estructuras/lista.hpp"
#include "../include/gameplay.hpp"
#include "../include/company.hpp"
#include "../include/node.hpp"
#include <string>

void draw_bar(sf::RenderWindow &window, sf::Text &progress_bar_textt, Gameplay &gameplay_status);

void draw_company_information
(
    sf::RenderWindow &window,
    sf::Font &font,
    const std::string &company_name,
    Node *company_node,
    Company *company
);

void popup_console_window
(
    const std::string &user_input,
    const std::string &command_required,
    sf::Text &command_required_text,
    sf::Text &input_command_text,
    sf::Clock &console_time,
    sf::RectangleShape &time_bar
);

