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
    // Initialize the power tree with 4 levels (15 nodes total)
    power_tree.insert(Product("Root Power", "The base power", 100));
    
    power_tree.insert(Product("Left Branch 1", "First left power", 50));
    power_tree.insert(Product("Right Branch 1", "First right power", 150));
    
    power_tree.insert(Product("Left Branch 2-1", "Second level left power", 25));
    power_tree.insert(Product("Left Branch 2-2", "Second level left power", 75));
    power_tree.insert(Product("Right Branch 2-1", "Second level right power", 125));
    power_tree.insert(Product("Right Branch 2-2", "Second level right power", 175));
    
    // Add more powers to complete the 4 levels
    power_tree.insert(Product("Left Branch 3-1", "Third level left power", 12));
    power_tree.insert(Product("Left Branch 3-2", "Third level left power", 37));
    power_tree.insert(Product("Left Branch 3-3", "Third level left power", 62));
    power_tree.insert(Product("Left Branch 3-4", "Third level left power", 87));
    power_tree.insert(Product("Right Branch 3-1", "Third level right power", 112));
    power_tree.insert(Product("Right Branch 3-2", "Third level right power", 137));
    power_tree.insert(Product("Right Branch 3-3", "Third level right power", 162));
    power_tree.insert(Product("Right Branch 3-4", "Third level right power", 187));
}

bool Store::initialize_store_icon() {
    if (!store_icon_texture.loadFromFile("assets/images/store_icon.png")) {
        std::cerr << "Failed to load store icon." << std::endl;
        return false;
    }
    store_icon_sprite.setTexture(store_icon_texture);
    return true;
}

void Store::set_store_icon_position(float x, float y) {
    store_icon_sprite.setPosition(x, y);
}

void Store::toggle_store() {
    is_store_open = !is_store_open;
}

void Store::handle_click(float x, float y) {
    sf::FloatRect icon_bounds = store_icon_sprite.getGlobalBounds();
    if (icon_bounds.contains(x, y)) {
        toggle_store();
    }
    
    if (is_store_open) {
        // Handle clicks on the power tree
        // This would involve checking if the click is on a power node
        // and performing the appropriate action (purchase, unlock, etc.)
    }
}

void Store::draw_power_tree(sf::RenderWindow& window) {
    // Implement the drawing of the power tree here
    // This would involve traversing the tree and drawing each node
    // You may want to use SFML shapes and text to represent the nodes
}

void Store::update(sf::RenderWindow& window) {
    // Update logic for the store
    // This could involve updating the state of powers based on game progress
}

void Store::draw(sf::RenderWindow& window) {
    window.draw(store_icon_sprite);
    
    if (is_store_open) {
        draw_power_tree(window);
    }
}