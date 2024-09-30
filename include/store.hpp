#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "../include/estructuras/arbol_busqueda_binaria.hpp"
#include "../include/estructuras/arbol_binario.hpp"
#include "../include/estructuras/lista.hpp"
#include "../include/gameplay.hpp"
#include "../include/user.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

class Product
{
    std::string name{};
    std::string description{};
    int price{};
    bool is_purchased{ false };
    bool is_locked{ true };
    sf::Vector2f position{};

public:
    Product() = default;
    Product(const std::string &product_name, const std::string &product_description, int product_price);

    void purchase();
    void unlock();

    std::string get_name() const;
    std::string get_description() const;
    int get_price() const;
    bool is_product_purchased() const;
    bool is_product_locked() const;
    void set_position(float x, float y);
    void set_is_purchased(bool purchased);
    void set_is_locked(bool locked);
    sf::Vector2f get_position() const;

    bool operator < (const Product& other) const;
    bool operator > (const Product& other) const;
    bool operator == (const Product& other) const;
};

class Store
{
    ArbolBusquedaBinaria<Product> power_tree{};
    sf::Texture store_icon_texture{};
    sf::Sprite store_icon_sprite{};
    bool _is_store_open{};
    Lista<ArbolBinario<Product>*> pre_order_products{};

    void initialize_power_tree();
    void update_pre_order_products();
    void draw_power_tree(sf::RenderWindow& window, const sf::Font& font, User &user);

    void attempt_purchase
    (
        ArbolBinario<Product> *product_node,
        sf::Text &coin_text,
        User &user,
        Gameplay &gameplay_status
    );

    void collect_pre_order_products(ArbolBinario<Product> *node);

public:
    Store();

    void initialize_store_icon();
    void set_store_icon_position(float x, float y);
    void toggle_store();
    bool is_store_open() const { return _is_store_open; }
    void handle_click(float x, float y, sf::Text &coin_text, User &user, Gameplay &gameplay_status);
    void draw(sf::RenderWindow& window, const sf::Font& font, User &user);
    void set_product_position(const std::string& product_name, float x, float y);
};