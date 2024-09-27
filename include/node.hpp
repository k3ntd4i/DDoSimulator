#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Node
{
    sf::CircleShape node{};
    bool infected{};
    bool available{};
    bool successfully_attacked{};
    sf::Clock clock{};

public:
    Node()
        : infected{ false }
        , available{ false }
        , successfully_attacked{ false }
    {
        node.setOrigin(15.f, 15.f);
        node.setRadius(11);
        node.setFillColor(sf::Color::Black);
        node.setOutlineColor(sf::Color::White);
        node.setOutlineThickness(-1);
    }

    sf::CircleShape &get_circle() { return node; }
    bool is_infected() { return infected; }
    bool is_available() { return available; }
    bool was_successfully_attacked() { return successfully_attacked; }
    float get_elapsed_seconds() { return clock.getElapsedTime().asSeconds(); }
    void set_status_available(bool status) { this->available = status; }
    void set_status_infected(bool status) { this->infected = status; }
    void set_attack_result(bool successful) { this->successfully_attacked = successful; }
};