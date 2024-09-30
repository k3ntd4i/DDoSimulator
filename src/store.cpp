#include "../include/store.hpp"

Product::Product(const std::string &product_name, const std::string &product_description, int product_price)
    : name{ product_name }
    , description{ product_description }
    , price{ product_price }
    , is_purchased{ false }
    , is_locked{ true }
{
}

void Product::purchase() { is_purchased = true; }
void Product::unlock() { is_locked = true; }
std::string Product::get_name() const { return name; }
std::string Product::get_description() const { return description; }
int Product::get_price() const { return price; }
bool Product::is_product_purchased() const { return is_purchased; }
bool Product::is_product_locked() const { return is_locked; }
void Product::set_position(float x, float y) { position = sf::Vector2f(x, y); }
void Product::set_is_purchased(bool purchased) { this->is_purchased = purchased; }
void Product::set_is_locked(bool locked) { this->is_locked = locked; }
sf::Vector2f Product::get_position() const { return position; }

bool Product::operator < (const Product& other) const { return (this->price < other.price); }
bool Product::operator > (const Product& other) const { return (this->price > other.price); }
bool Product::operator == (const Product& other) const { return (this->price == other.price); }

Store::Store()
{
    initialize_power_tree();
    update_pre_order_products();
}

void Store::initialize_power_tree()
{
    power_tree.insert(Product("Exploit Enhancer", "    Increases attack power by 1\nand removes 1 word from terminal", 10));
    power_tree.insert(Product("Firewall Bypass", "Removes 1 word from terminal", 7));
    power_tree.insert(Product("DDoS Amplifier", "Increases attack power by 5", 14));
    power_tree.insert(Product("Ultimate Exploit", "Increases attack power by 50", 34));
    power_tree.insert(Product("Zero-Day Surge", "Increases attack power by 12", 12));
    power_tree.insert(Product("Code Injection", "Removes 1 word from terminal", 5));
    power_tree.insert(Product("Packet Sniffer", "Removes 1 word from terminal", 4));
    power_tree.insert(Product("Rootkit Reducer", "Removes 1 word from terminal", 8));
    power_tree.insert(Product("Malware Minimizer", "Removes 1 word from terminal", 9));
    power_tree.insert(Product("Brute Force Multiplier", "Increases attack power by 22", 11));
}

void Store::update_pre_order_products()
{
    while (!pre_order_products.is_empty())
    {
        pre_order_products.remove(0);
    }

    collect_pre_order_products(power_tree.get_root());
}

void Store::collect_pre_order_products(ArbolBinario<Product> *node)
{
    if (node == nullptr)
    {
        return;
    }

    pre_order_products.insert(pre_order_products.size(), node);
    collect_pre_order_products(node->get_right_child());
    collect_pre_order_products(node->get_left_child());
}

/**
 * @throw std::runtime_error si el asset necesario no fue encontrado
 */
void Store::initialize_store_icon()
{
    if (!store_icon_texture.loadFromFile("./assets/images/store_icon.png"))
    {
        throw std::runtime_error{ "The coin texture could not be loaded." };
    }

    store_icon_sprite.setTexture(store_icon_texture);
    store_icon_sprite.setScale(0.17f, 0.17f);
    set_store_icon_position(26.f, 619.f);

    set_product_position("Exploit Enhancer", 610.f, 531.f);
    set_product_position("Firewall Bypass", 730.f, 468.f);
    set_product_position("Code Injection", 819.f, 408.f);
    set_product_position("Packet Sniffer", 819.f, 286.f);
    set_product_position("Rootkit Reducer", 661.f, 334.f);
    set_product_position("Malware Minimizer", 661.f, 232.f);
    set_product_position("DDoS Amplifier", 494.f, 468.f);
    set_product_position("Zero-Day Surge", 558.f, 334.f);
    set_product_position("Brute Force Multiplier", 557.f, 232.f);
    set_product_position("Ultimate Exploit", 407.f, 408.f);
}

void Store::set_store_icon_position(float x, float y)
{
    store_icon_sprite.setPosition(x, y);
}

void Store::toggle_store()
{
    store_open = !store_open;
}

void Store::attempt_purchase
(
    ArbolBinario<Product> *product_node,
    sf::Text &coin_text,
    User &user,
    Gameplay &gameplay_status
)
{
    if (user.get_yuca_coins() < product_node->get_element().get_price())
    {
        std::cout << "\nNot enough Yuca Coins to purchase: " << product_node->get_element().get_name() << '\n';
    }
    else if (product_node->get_element().is_product_locked())
    {
        std::cout << "\nThe product is not unlocked: " << product_node->get_element().get_name() << '\n';
    }
    else if (!product_node->get_element().is_product_purchased())
    {
        std::cout << "\nPurchased power: " << product_node->get_element().get_name() << '\n';

        user.update_yuca_coins_wallet(-(product_node->get_element().get_price()));
        coin_text.setString( std::to_string(user.get_yuca_coins()) );

        product_node->get_element().purchase();

        if (product_node->get_left_child() != nullptr)
        {
            std::cout << "\nDESBLOQUEADO: " << product_node->get_left_child()->get_element().get_name() << '\n';
            product_node->get_left_child()->get_element().set_is_locked(false);
        }

        if (product_node->get_right_child() != nullptr)
        {
            std::cout << "\nDESBLOQUEADO: " << product_node->get_right_child()->get_element().get_name() << '\n';
            product_node->get_right_child()->get_element().set_is_locked(false);
        }

        std::string product_description{ product_node->get_element().get_description() };

        if (product_node->get_element().get_price() == 10)
        {
            gameplay_status.decrease_quantity_words();
            user.increase_hack_intensity(1);
        }
        else if (product_node->get_element().get_price() < 10)
        {
            gameplay_status.decrease_quantity_words();
        }
        else if (product_node->get_element().get_price() > 10)
        {
            user.increase_hack_intensity(std::stoi(product_description.substr(product_description.find_last_of(' ') + 1)));
        }

        product_node->get_element().set_is_purchased(true);
    }
}

void Store::handle_click(float x, float y, sf::Text &coin_text, User &user, Gameplay &gameplay_status)
{
    sf::FloatRect icon_bounds{ store_icon_sprite.getGlobalBounds() };

    if (icon_bounds.contains(x, y))
    {
        toggle_store();
    }
    else if (is_store_open())
    {
        ArbolBinario<Product> *product{};
        for (int i{0}; i < pre_order_products.size(); ++i)
        {
            product = pre_order_products.get(i);
            sf::CircleShape node{ 40.f };
            node.setPosition(product->get_element().get_position());

            if (node.getGlobalBounds().contains(x, y))
            {
                attempt_purchase(product, coin_text, user, gameplay_status);
                break;
            }
        }
    }
}

void Store::draw_power_tree(sf::RenderWindow& window, const sf::Font& font, User &user)
{
    static sf::RectangleShape background_block{ sf::Vector2f{ 1140.f, 720.f } };
    background_block.setPosition(114.f,0.f);
    background_block.setFillColor(sf::Color(0, 0, 0, 190));
    window.draw(background_block);

    static sf::Texture shop_background_texture{};
    if (!shop_background_texture.loadFromFile("assets/images/shop_background.png"))
    {
        std::cerr << "Failed to load shop background image." << '\n';
        return;
    }

    sf::Sprite shop_background_sprite{ shop_background_texture };
    static float background_width{ 960.f };
    static float background_height{ 540.f };

    shop_background_sprite.setScale
    (
        background_width / shop_background_texture.getSize().x,
        background_height / shop_background_texture.getSize().y
    );

    shop_background_sprite.setPosition(160.f, 90.f);

    window.draw(shop_background_sprite);

    static sf::RectangleShape store_window_border{ sf::Vector2f{ background_width, background_height } };
    store_window_border.setFillColor(sf::Color::Transparent);
    store_window_border.setOutlineColor(sf::Color::White);
    store_window_border.setOutlineThickness(2.f);
    store_window_border.setPosition(160.f, 90.f);
    window.draw(store_window_border);

    static sf::Texture nodes_texture{};
    if (!nodes_texture.loadFromFile("assets/images/nodes_texture.png"))
    {
        std::cerr << "The texture could not be loaded." << '\n';
        return;
    }

    sf::Sprite node{ nodes_texture };

    // Dibujar nodos de los productos
    Product *product{};
    for (int i{0}; i < pre_order_products.size(); ++i)
    {
        product = &pre_order_products.get(i)->get_element();
        node.setScale(0.25f, 0.25f);

        node.setPosition(product->get_position());

        if (product->is_product_locked())
        {
            node.setColor(sf::Color{ 255, 255, 255, 255 });
            node.setTextureRect(sf::IntRect(720, 0, 240, 240));
        }
        else if (!product->is_product_purchased())
        {
            if (user.get_yuca_coins() < product->get_price())
            {
                node.setColor(sf::Color{ 255, 255, 255, 70 });
            }
            else
            {
                node.setColor(sf::Color{ 255, 255, 255, 255 });
            }

            if (product->get_price() == 10)
            {
                node.setTextureRect(sf::IntRect(480, 0, 240, 240));
            }
            else if (product->get_price() < 10)
            {
                node.setTextureRect(sf::IntRect(0, 0, 240, 240));
            }
            else if (product->get_price() > 10)
            {
                node.setTextureRect(sf::IntRect(240, 0, 240, 240));
            }
        }
        else
        {
            node.setColor(sf::Color{ 255, 255, 255, 255 });
            node.setTextureRect(sf::IntRect(960, 0, 240, 240));
        }

        window.draw(node);

        if (node.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
        {
            static sf::Text name{};
            name.setFont(font);
            name.setCharacterSize(20);
            name.setString(product->get_name());

            static sf::Text price{};
            price.setFont(font);
            price.setCharacterSize(20);
            price.setString(std::to_string(product->get_price()) + " yucacoins");

            static sf::Text information{};
            information.setFont(font);
            information.setCharacterSize(20);
            information.setString(product->get_description());

            if (product->get_price() == 10)
            {
                name.setPosition(static_cast<int>(640 - (name.getGlobalBounds().width / 2)), 117.f);
                price.setPosition(static_cast<int>(640 - (price.getGlobalBounds().width / 2)), 137.f);
                information.setPosition(static_cast<int>(640 - (information.getGlobalBounds().width / 2)), 158.f);
            }
            else
            {
                name.setPosition(static_cast<int>(640 - (name.getGlobalBounds().width / 2)), 127.f);
                price.setPosition(static_cast<int>(640 - (price.getGlobalBounds().width / 2)), 147.f);
                information.setPosition(static_cast<int>(640 - (information.getGlobalBounds().width / 2)), 168.f);
            }

            window.draw(name);
            window.draw(price);
            window.draw(information);
        }
    }
}

void Store::draw(sf::RenderWindow& window, const sf::Font& font, User &user)
{
    window.draw(store_icon_sprite);

    if (is_store_open())
    {
        draw_power_tree(window, font, user);
    }
}

void Store::set_product_position(const std::string& product_name, float x, float y)
{
    Product *product{};
    for (int i{0}; i < pre_order_products.size(); ++i)
    {
        product = &pre_order_products.get(i)->get_element();

        if (product->get_price() == 10)
        {
            product->set_is_locked(false);
        }

        if (product->get_name() == product_name)
        {
            product->set_position(x, y);
            break;
        }
    }
}