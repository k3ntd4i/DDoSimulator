#include "../include/store.hpp"
#include <stdexcept>

Product::Product(const std::string& product_name, const std::string& product_description, int product_price)
    : name{product_name}, description{product_description}, price{product_price} {}

void Product::purchase() {
    is_purchased = true;
}

void Product::unlock() {
    is_unlocked = true;
}

std::optional<std::string> Product::get_name() const {
    return name;
}

std::optional<std::string> Product::get_description() const {
    return description;
}

std::optional<int> Product::get_price() const {
    return price;
}

bool Product::is_product_purchased() const {
    return is_purchased;
}

bool Product::is_product_unlocked() const {
    return is_unlocked;
}

bool Product::operator<(const Product& other) const {
    return price < other.price;
}

bool Product::operator>(const Product& other) const {
    return price > other.price;
}

bool Product::operator==(const Product& other) const {
    return price == other.price;
}


Store::Store() {
    initialize_power_tree();
}

void Store::initialize_power_tree() {
   
    power_tree.insert(Product("Root Power uwu", "The base power", 75)); 
    power_tree.insert(Product("Left Branch 1", "First left power", 50));
    power_tree.insert(Product("Right Branch 1", "First right power", 150));
    power_tree.insert(Product("Left Branch 2-1", "Second level left power", 25));
    power_tree.insert(Product("Left Branch 2-2", "Second level left power", 75));
    power_tree.insert(Product("Right Branch 2-1", "Second level right power", 125));
    power_tree.insert(Product("Right Branch 2-2", "Second level right power", 175));
    power_tree.insert(Product("Left Branch 3-1", "Third level left power", 12));
    power_tree.insert(Product("Left Branch 3-2", "Third level left power", 37));
    power_tree.insert(Product("Left Branch 3-3", "Third level left power", 62));
}

bool Store::initialize_store_icon() {
    if (!store_icon_texture.loadFromFile("./assets/images/store_icon.png")) {
        std::cerr << "Failed to load store icon.";
        return false;
    }
    store_icon_sprite.setTexture(store_icon_texture);

    store_icon_sprite.setScale(0.17f,0.17f);

    set_store_icon_position(26.f, 619.f);
    return true;
}

void Store::set_store_icon_position(float x, float y) {
    store_icon_sprite.setPosition(x, y);
}

void Store::toggle_store() {
    _is_store_open = !_is_store_open;
}

void Store::handle_click(float x, float y) {
    sf::FloatRect icon_bounds = store_icon_sprite.getGlobalBounds();
    if (icon_bounds.contains(x, y)) {
        toggle_store();
    }
    /*
    if (is_store_open()) {

    }*/
}

void Store::draw_power_tree(sf::RenderWindow& window) {
    // Fondo translúcido para la ventana emergente
    sf::RectangleShape background_block{ sf::Vector2f{ 1280.f, 720.f } };
    background_block.setFillColor(sf::Color(0, 0, 0, 150));  // Fondo negro translúcido

    // Ventana de la tienda
    sf::RectangleShape store_window{ sf::Vector2f{ 800.f, 600.f } };
    store_window.setFillColor(sf::Color::White);
    store_window.setOutlineColor(sf::Color::Green);
    store_window.setOutlineThickness(5.f);
    store_window.setPosition(240.f, 60.f);  // Centramos la ventana

    // Título de la tienda
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/digital.TTF")) {
        throw std::runtime_error{ "The font could not be loaded." };
    }
    sf::Text store_title{ "Welcome Dark Web - Buy Powers", font, 45 };
    store_title.setFillColor(sf::Color::Black);
    store_title.setPosition(320.f, 80.f);  

    // Dibujar todos los elementos fijos
    window.draw(background_block);
    window.draw(store_window);
    window.draw(store_title);

    // Dibujar el árbol de poderes
    // Aquí recorremos el árbol para dibujar sus nodos
    draw_binary_tree(window, this->power_tree, font);
}

void Store::draw_binary_tree_recursively(sf::RenderWindow& window, ArbolBinario<Product>* node, 
                                         sf::Vector2f position, float offset_x, const sf::Font& font) {
    if (node == nullptr) {
        return;  // Caso base de la recursión: si el nodo es nulo, terminamos
    }

    // Dibujar el nodo actual
    sf::CircleShape tree_node(40.f);
    tree_node.setPosition(position);
    tree_node.setFillColor(sf::Color::Green);
    window.draw(tree_node);

    // Dibujar el nombre del poder dentro del nodo
    sf::Text node_text{ node->get_element().get_name().value_or("Unnamed"), font, 20 };
    node_text.setFillColor(sf::Color::Black);
    node_text.setPosition(position.x + 10.f, position.y + 10.f);
    window.draw(node_text);

    // Definir las posiciones para los hijos
    float child_y_position = position.y + 100.f;
    sf::Vector2f left_child_position(position.x - offset_x, child_y_position);
    sf::Vector2f right_child_position(position.x + offset_x, child_y_position);

    // Recorrer los hijos de manera recursiva
    draw_binary_tree_recursively(window, node->get_left_child(), left_child_position, offset_x / 2, font);
    draw_binary_tree_recursively(window, node->get_right_child(), right_child_position, offset_x / 2, font);
}

void Store::draw_binary_tree(sf::RenderWindow& window, ArbolBusquedaBinaria<Product>& tree, const sf::Font& font) {
    // Iniciar el dibujo del árbol desde la raíz, con la posición inicial y un offset para los hijos
    draw_binary_tree_recursively(window, tree.get_root(), sf::Vector2f(540.f, 200.f), 200.f, font);
}


void Store::update(sf::RenderWindow& window) {

}

void Store::draw(sf::RenderWindow& window) {
    window.draw(store_icon_sprite);
    
    if (is_store_open()) {
        draw_power_tree(window);
    }
}