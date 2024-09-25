#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "../include/estructuras/tabla_hash.hpp"
#include "../include/estructuras/grafo_simple.hpp"
#include "../include/company.hpp"
#include <stdexcept>
#include <fstream>
#include <string>

void initialize_window(sf::RenderWindow &window);
void initialize_map(sf::Texture &texture_background, sf::Sprite &sprite_background);
void initialize_font(sf::Font &font);
void initialize_progress_bar_text(sf::Font &font, sf::Text &text);
void initialize_time_text(sf::Font &font, sf::Text &countdown_text);
void initialize_console_text(sf::Font &font, sf::Text &words_text);
void initialize_console_input_text(sf::Font &font, sf::Text &input_text);
void initialize_words(std::string *array_words);
void initialize_company_network(GrafoSimple<sf::CircleShape*> &company_network);

void initialize_console_window
(
    sf::RectangleShape &translucent_background,
    sf::RectangleShape &console,
    sf::RectangleShape &text_field
);