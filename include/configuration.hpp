#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <stdexcept>

void initialize_window(sf::RenderWindow &window);
void initialize_map(sf::Texture &texture_background, sf::Sprite &sprite_background);
void initialize_text(sf::Font &font, sf::Text &text);
void initialize_time_text(sf::Font &font, sf::Text &countdown_text);