#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

void draw_countdown(sf::RenderWindow &window, sf::Clock &clock, sf::Time &countdown_time, sf::Text &countdown_text);