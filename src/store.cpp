#include "../include/store.hpp"

Product::Product(const std::string& product_name, const std::string& product_description, int product_price)
    : name{product_name}, description{product_description}, price{product_price} {}

void Product::purchase() { is_purchased = true; }
void Product::unlock() { is_unlocked = true; }
std::string Product::get_name() const { return name; }
std::string Product::get_description() const { return description; }
int Product::get_price() const { return price; }
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
    power_tree.insert(Product("Exploit Enhancer", "Increases attack power by 1 and removes 1 word from terminal", 10));
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

void Store::attempt_purchase(Product &product, sf::Text &coin_text, User &user, Gameplay &gameplay_status)
{
    if (user.get_yuca_coins() < product.get_price())
    {
        std::cout << "Not enough Yuca Coins to purchase" << product.get_name() << '\n';
    }
    // else if (!product.is_product_unlocked())
    // {
    //     std::cout << "The product is not unlocked" << product.get_name() << '\n';
    // }
    else if (!product.is_product_purchased())
    {
        std::cout << "Purchased power: " << product.get_name() << '\n';
        user.update_yuca_coins_wallet(-(product.get_price()));
        coin_text.setString( std::to_string(user.get_yuca_coins()) );
        product.purchase();

        std::string product_description{ product.get_description() };

        if (product.get_price() == 10)
        {
            gameplay_status.decrease_quantity_words();
            user.increase_hack_intensity(1);
        }
        else if (product_description.starts_with("Increases"))
        {
            user.increase_hack_intensity(std::stoi(product_description.substr(product_description.find_last_of(' ') + 1)));
        }
        else if (product.get_description().starts_with("Removes"))
        {
            gameplay_status.decrease_quantity_words();
        }
    }
}

void Store::handle_click(float x, float y, sf::Text &coin_text, User &user, Gameplay &gameplay_status)
{
    sf::FloatRect icon_bounds = store_icon_sprite.getGlobalBounds();

    if (icon_bounds.contains(x, y))
    {
        toggle_store();
    }
    else if (is_store_open())
    {
        for (auto &product : pre_order_products)
        {
            sf::CircleShape node(40.f);
            node.setPosition(product.get_position());

            if (node.getGlobalBounds().contains(x, y))
            {
                attempt_purchase(product, coin_text, user, gameplay_status);
                break;
            }
        }
    }
}


void Store::draw_power_tree(sf::RenderWindow& window, const sf::Font& font, User &user) {
    
    // Dibujar el fondo transparente de la tienda
    sf::RectangleShape background_block{ sf::Vector2f{ 1140.f, 720.f } };
    background_block.setPosition(114.f,0.f);
    background_block.setFillColor(sf::Color(0, 0, 0, 190));
    window.draw(background_block);

    // Cargar y dibujar la imagen de fondo de la tienda
    sf::Texture shop_background_texture;
    if (!shop_background_texture.loadFromFile("assets/images/shop_background.png")) {
        std::cerr << "Failed to load shop background image." << '\n';
        return;
    }

    sf::Sprite shop_background_sprite(shop_background_texture);
    // Escalar la imagen para que mantenga sus proporciones originales (960x540)
    float background_width = 960.f;
    float background_height = 540.f;
    float scale_x = background_width / shop_background_texture.getSize().x;
    float scale_y = background_height / shop_background_texture.getSize().y;
    shop_background_sprite.setScale(scale_x, scale_y);
    shop_background_sprite.setPosition(160.f, 90.f); // Centrar la imagen en la ventana (1280x720)

    window.draw(shop_background_sprite);

    // Dibujar el borde de la ventana de la tienda
    sf::RectangleShape store_window_border{ sf::Vector2f{ background_width, background_height } };
    store_window_border.setFillColor(sf::Color::Transparent);
    store_window_border.setOutlineColor(sf::Color::White);
    store_window_border.setOutlineThickness(2.f);
    store_window_border.setPosition(160.f, 90.f); // Alinear con la imagen de fondo
    window.draw(store_window_border);


    //codigo aqu ixdd
    sf::Texture nodes_texture;
    if (!nodes_texture.loadFromFile("assets/images/nodes_texture.png")) {
        std::cerr << "The texture could not be loaded." << '\n';
        return;
    }

    float node_radius = 30.f;
    sf::Sprite node(nodes_texture);
    // Dibujar nodos de los productos
    for (const auto& product : pre_order_products) {
        
        node.setScale(0.25f, 0.25f);
        
        node.setPosition(product.get_position());
        if (user.get_yuca_coins() >= product.get_price() && !product.is_product_purchased())
        {
            node.setTextureRect(sf::IntRect(0, 0, 240, 240));
        }
        else if (product.is_product_purchased())
        {
            node.setTextureRect(sf::IntRect(960, 0, 240, 240));
        }
        else
        {
            node.setTextureRect(sf::IntRect(720, 0, 240, 240));
        }
        
        window.draw(node);

    }
}

/*
void Store::update(sf::RenderWindow& window) {
    // Any update logic if needed
}
*/

void Store::draw(sf::RenderWindow& window, const sf::Font& font, User &user) {
    window.draw(store_icon_sprite);
    
    if (is_store_open()) {
        draw_power_tree(window, font, user);
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