#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "../include/estructuras/lista.hpp"
#include "../include/gameplay.hpp"
#include <string>

void draw_bar(sf::RenderWindow &window, sf::Text &progress_bar_textt, Gameplay &gameplay_status);

void popup_console_window
(
    const std::string &user_input,
    const std::string &command_required,
    sf::Text &command_required_text,
    sf::Text &input_command_text
);

