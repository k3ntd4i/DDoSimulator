#include "../include/store.hpp"
#include <stdexcept>

Product::Product(const std::string& product_name, const std::string& product_description, int product_price)
    : name{product_name}, description{product_description}, price{product_price} {}

void Product::purchase() { is_purchased = true; }
void Product::unlock() { is_unlocked = true; }
std::optional<std::string> Product::get_name() const { return name; }
std::optional<std::string> Product::get_description() const { return description; }
std::optional<int> Product::get_price() const { return price; }
bool Product::is_product_purchased() const { return is_purchased; }
bool Product::is_product_unlocked() const { return is_unlocked; }
void Product::set_position(float x, float y) { position = sf::Vector2f(x, y); }
sf::Vector2f Product::get_position() const { return position; }

bool Product::operator<(const Product& other) const { return price < other.price; }
bool Product::operator>(const Product& other) const { return price > other.price; }
bool Product::operator==(const Product& other) const { return price == other.price; }

Store::Store() {
    initialize_power_tree();
    update_pre_order_products();
}

void Store::initialize_power_tree() {
    power_tree.insert(Product("Exploit Enhancer", "Increases attack power by 1", 10));
    power_tree.insert(Product("Firewall Bypass", "Removes 1 word from terminal", 7));
    power_tree.insert(Product("Code Injection", "Removes 1 word from terminal", 5));
    power_tree.insert(Product("Packet Sniffer", "Removes 1 word from terminal", 4));
    power_tree.insert(Product("Rootkit Reducer", "Removes 1 word from terminal", 6));
    power_tree.insert(Product("Malware Minimizer", "Removes 1 word from terminal", 8));
    power_tree.insert(Product("DDoS Amplifier", "Increases attack power by 5", 13));
    power_tree.insert(Product("Zero-Day Surge", "Increases attack power by 12", 12));
    power_tree.insert(Product("Brute Force Multiplier", "Increases attack power by 24", 11));
    power_tree.insert(Product("Ultimate Exploit", "Increases attack power by 50", 38));
}

void Store::update_pre_order_products() {
    pre_order_products.clear();
    collect_pre_order_products(power_tree.get_root());
}

void Store::collect_pre_order_products(ArbolBinario<Product>* node) {
    if (node == nullptr) {
        return;
    }
    pre_order_products.push_back(node->get_element());
    collect_pre_order_products(node->get_right_child());
    collect_pre_order_products(node->get_left_child());
}

bool Store::initialize_store_icon() {
    if (!store_icon_texture.loadFromFile("./assets/images/store_icon.png")) {
        std::cerr << "Failed to load store icon.";
        return false;
    }
    store_icon_sprite.setTexture(store_icon_texture);
    store_icon_sprite.setScale(0.17f, 0.17f);
    set_store_icon_position(26.f, 619.f);
    return true;
}

void Store::set_store_icon_position(float x, float y) {
    store_icon_sprite.setPosition(x, y);
}

void Store::toggle_store() {
    _is_store_open = !_is_store_open;
}

bool Store::attempt_purchase(const Product& product) {
    if (yuca_coins >= product.get_price().value_or(0)) {
        yuca_coins -= product.get_price().value_or(0);
        std::cout << "Purchased power: " << product.get_name().value_or("Unknown") << std::endl;
        return true;
    } else {
        std::cout << "Not enough Yuca Coins to purchase " << product.get_name().value_or("Unknown") << std::endl;
        return false;
    }
}

void Store::handle_click(float x, float y, const sf::Font& font) {
    sf::FloatRect icon_bounds = store_icon_sprite.getGlobalBounds();
    if (icon_bounds.contains(x, y)) {
        toggle_store();
    } else if (is_store_open()) {
        for (const auto& product : pre_order_products) {
            sf::CircleShape node(40.f);
            node.setPosition(product.get_position());
            if (node.getGlobalBounds().contains(x, y)) {
                attempt_purchase(product);
                break;
            }
        }
    }
}

void Store::draw_power_tree(sf::RenderWindow& window, const sf::Font& font) {
    sf::RectangleShape background_block{ sf::Vector2f{ 1280.f, 720.f } };
    background_block.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(background_block);

    sf::RectangleShape store_window{ sf::Vector2f{ 800.f, 600.f } };
    store_window.setFillColor(sf::Color::White);
    store_window.setOutlineColor(sf::Color::Green);
    store_window.setOutlineThickness(5.f);
    store_window.setPosition(240.f, 60.f);
    window.draw(store_window);

    sf::Text store_title{ "Welcome Dark Web - Buy Powers", font, 45 };
    store_title.setFillColor(sf::Color::Black);
    store_title.setPosition(320.f, 80.f);
    window.draw(store_title);

    sf::Text coins_text{ "Yuca Coins: " + std::to_string(yuca_coins), font, 30 };
    coins_text.setFillColor(sf::Color::Black);
    coins_text.setPosition(800.f, 120.f);
    window.draw(coins_text);

    for (const auto& product : pre_order_products) {
        sf::CircleShape node(40.f);
        node.setPosition(product.get_position());
        node.setFillColor(yuca_coins >= product.get_price().value_or(0) ? sf::Color::Green : sf::Color::Red);
        window.draw(node);

        sf::Text node_text{ product.get_name().value_or("Unnamed"), font, 20 };
        node_text.setFillColor(sf::Color::Black);
        node_text.setPosition(product.get_position().x + 10.f, product.get_position().y + 10.f);
        window.draw(node_text);
    }
}

void Store::update(sf::RenderWindow& window) {
    // Any update logic if needed
}

void Store::draw(sf::RenderWindow& window, const sf::Font& font) {
    window.draw(store_icon_sprite);
    
    if (is_store_open()) {
        draw_power_tree(window, font);
    }
}

void Store::set_product_position(const std::string& product_name, float x, float y) {
    for (auto& product : pre_order_products) {
        if (product.get_name() == product_name) {
            product.set_position(x, y);
            break;
        }
    }
}