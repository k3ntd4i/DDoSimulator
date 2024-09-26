#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "../include/estructuras/lista.hpp"
#include <string>
#include <iostream>

void draw_bar(sf::RenderWindow &window, sf::Text &progress_bar_textt);

void popup_console_window
(
    const std::string &user_input,
    const std::string &command_required,
    sf::Text &command_required_text,
    sf::Text &input_command_text
);