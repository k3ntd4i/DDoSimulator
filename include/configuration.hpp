#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

void initialize_window(sf::RenderWindow &window, sf::View &view);
void initialize_map(sf::Texture &texture_background, sf::Sprite &sprite_background);