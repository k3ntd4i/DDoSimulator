#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "../include/estructuras/arbol_busqueda_binaria.hpp"
#include "../include/gameplay.hpp"
#include "../include/user.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

class Product {
private:
    std::string name{};
    std::string description{};
    int price{};
    bool is_purchased{false};
    bool is_unlocked{false};
    sf::Vector2f position{};

public:
    Product() = default;
    Product(const std::string& product_name, const std::string& product_description, int product_price);

    void purchase();
    void unlock();
    
    std::string get_name() const;
    std::string get_description() const;
    int get_price() const;
    bool is_product_purchased() const {return is_purchased;}
    bool is_product_unlocked() const {return is_unlocked;}
    void set_position(float x, float y);
    void set_is_purchased(bool purchased) { this->is_purchased = purchased; }
    void set_is_unlocked(bool unlocked) { this->is_unlocked = unlocked; }
    sf::Vector2f get_position() const;

    bool operator<(const Product& other) const;
    bool operator>(const Product& other) const;
    bool operator==(const Product& other) const;
};

class Store {
private:
    ArbolBusquedaBinaria<Product> power_tree{};
    sf::Texture store_icon_texture{};
    sf::Sprite store_icon_sprite{};
    bool _is_store_open{false};
    std::vector<Product> pre_order_products{};

    void initialize_power_tree();
    void update_pre_order_products();
    void draw_power_tree(sf::RenderWindow& window, const sf::Font& font, User &user);
    void attempt_purchase(Product &product, sf::Text &coin_text, User &user, Gameplay &gameplay_status);
    void collect_pre_order_products(ArbolBinario<Product>* node);

public:
    Store();

    bool initialize_store_icon();
    void set_store_icon_position(float x, float y);
    void toggle_store();
    bool is_store_open() const { return _is_store_open; }
    void handle_click(float x, float y, sf::Text &coin_text, User &user, Gameplay &gameplay_status);
    void draw(sf::RenderWindow& window, const sf::Font& font, User &user);
    void set_product_position(const std::string& product_name, float x, float y);
    ArbolBinario<Product>* get_power_tree_root() { return power_tree.get_root(); }
};