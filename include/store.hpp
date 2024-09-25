#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "../include/estructuras/arbol_busqueda_binaria.hpp"
#include <string>
#include <iostream>
#include <optional>

class Product {
private:
    std::string name{};
    std::string description{};
    int price{};
    bool is_purchased{false};
    bool is_unlocked{false};

public:
    Product() = default;
    Product(const std::string& product_name, const std::string& product_description, int product_price);

    void purchase();
    void unlock();
    
    std::optional<std::string> get_name() const;
    std::optional<std::string> get_description() const;
    std::optional<int> get_price() const;
    bool is_product_purchased() const;
    bool is_product_unlocked() const;

    bool operator<(const Product& other) const;
    bool operator>(const Product& other) const;
    bool operator==(const Product& other) const;
};

class Store {
private:
    ArbolBusquedaBinaria<Product> power_tree{};
    sf::Texture store_icon_texture{};
    sf::Sprite store_icon_sprite{};
    bool _is_store_open{false};  // Renamed member variable

    void initialize_power_tree();
    void draw_power_tree(sf::RenderWindow& window);

public:
    Store();
    
    bool initialize_store_icon();
    void set_store_icon_position(float x, float y);
    void toggle_store();
    bool is_store_open() const { 
        return _is_store_open;    
    }
    void handle_click(float x, float y);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};