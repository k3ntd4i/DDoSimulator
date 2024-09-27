#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "../include/estructuras/tabla_hash.hpp"
#include "../include/estructuras/grafo_simple.hpp"
#include "../include/estructuras/cola.hpp"
#include "../include/company.hpp"
#include "../include/node.hpp"

void verify_node_click
(
    sf::RenderWindow &window,
    GrafoSimple<Node*> &company_network,
    bool &click_flag,
    sf::Clock &console_time
);

void clear_conditional_objects
(
    Cola<std::string> &extracted_words,
    bool &click_flag,
    std::string &user_input
);