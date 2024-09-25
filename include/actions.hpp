#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "../include/estructuras/tabla_hash.hpp"
#include "../include/estructuras/grafo_simple.hpp"
#include "../include/company.hpp"

void verify_node_click
(
    sf::RenderWindow &window,
    GrafoSimple<sf::CircleShape*> &company_network,
    bool &click_flag,
    sf::Clock &console_time
);