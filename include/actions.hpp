#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "../include/estructuras/tabla_hash.hpp"
#include "../include/estructuras/grafo_simple.hpp"
#include "../include/estructuras/cola.hpp"
#include "../include/estructuras/lista.hpp"
#include "../include/company.hpp"
#include "../include/node.hpp"
#include "../include/user.hpp"
#include "../include/gameplay.hpp"
#include <string>

void verify_node_click
(
    sf::RenderWindow &window,
    GrafoSimple<Node*> &company_network,
    bool &click_flag,
    sf::Clock &console_time,
    int &company_index
);

void clear_conditional_objects
(
    Cola<std::string> &extracted_words,
    bool &click_flag,
    std::string &user_input,
    int &company_index
);

void user_fails_attack
(
    User &user,
    sf::Sprite &anonymity_sprite,
    GrafoSimple<Node*> &company_network,
    int company_index
);

void user_succeeds_attack
(
    User &user,
    sf::Text &coin_text,
    GrafoSimple<Node*> &company_network,
    TablaHash<Company*> &companies,
    Gameplay &gameplay_status,
    int company_index
);