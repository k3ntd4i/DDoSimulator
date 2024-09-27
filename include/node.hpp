#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <string>

class Node
{
    sf::CircleShape node{};
    std::string company_name{};
    bool infected{};
    bool available{};
    bool successfully_attacked{};
    bool just_attacked{};
    sf::Clock clock{};

public:
    Node(const std::string &new_name)
        : company_name{ new_name }
        , infected{ false }
        , available{ false }
        , successfully_attacked{ false }
        , just_attacked{ false }
    {
        node.setOrigin(16.f, 16.f);
        node.setRadius(11.f);
        node.setFillColor(sf::Color::Black);
        node.setOutlineColor(sf::Color::White);
        node.setOutlineThickness(-3.f);
    }

    sf::CircleShape &get_circle() { return node; }
    std::string get_company_name() { return company_name; }
    bool is_infected() { return infected; }
    bool is_available() { return available; }
    bool was_successfully_attacked() { return successfully_attacked; }
    bool was_just_attacked() { return just_attacked; }
    float get_elapsed_seconds() { return clock.getElapsedTime().asSeconds(); }
    void set_status_infected(bool status) { this->infected = status; }
    void set_status_available(bool status) { this->available = status; }
    void set_attack_result(bool successful) { this->successfully_attacked = successful; }
    void set_was_just_attacked(bool was_attacked) { this->just_attacked = was_attacked; }
    void reset_clock() { this->clock.restart(); }
};