#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

void draw_bar(sf::RenderWindow &window, sf::Text &progress_bar_textt);
void popup_console_window(sf::Text &words_text, sf::Text &input_text, std::string &user_input);