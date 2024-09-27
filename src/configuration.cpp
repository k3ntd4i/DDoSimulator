#include "../include/configuration.hpp"

void initialize_window(sf::RenderWindow &window)
{
    window.create
    (
        sf::VideoMode{ 1280, 720, sf::VideoMode::getDesktopMode().bitsPerPixel },
        "DDoSimulator"
    );

    window.setVerticalSyncEnabled(true);
}

/**
 * @throw std::runtime_error si el asset necesario no fue encontrado
 */
void initialize_map(sf::Texture &texture_background, sf::Sprite &sprite_background)
{
    if (!texture_background.loadFromFile(R"(assets\images\map.png)"))
    {
        throw std::runtime_error{ "The background could not be loaded." };
    }

    sprite_background.setTexture(texture_background);
    sprite_background.setScale(0.26f, 0.26f);
    sprite_background.setPosition(112.f, 76.f);
}

/**
 * @throw std::runtime_error si el asset necesario no fue encontrado
 */
void initialize_font(sf::Font &font)
{
    if (!font.loadFromFile(R"(assets\fonts\digital.TTF)"))
    {
        throw std::runtime_error{ "The font could not be loaded." };
    }
}

void initialize_progress_bar_text(sf::Font &font, sf::Text &text)
{
    text.setFont(font);
    text.setCharacterSize(35);
    text.setFillColor(sf::Color::White);
}

void initialize_time_text(sf::Font &font, sf::Text &countdown_text)
{
    countdown_text.setFont(font);
    countdown_text.setCharacterSize(60);
    countdown_text.setFillColor(sf::Color::White);
}

void initialize_console_text(sf::Font &font, sf::Text &words_text)
{
    words_text.setFont(font);
    words_text.setCharacterSize(45);
    words_text.setFillColor(sf::Color::Green);
}

void initialize_console_input_text(sf::Font &font, sf::Text &input_text)
{
    input_text.setFont(font);
    input_text.setCharacterSize(45);
    input_text.setFillColor(sf::Color::Black);
}

void initialize_console_window
(
    sf::RectangleShape &translucent_background,
    sf::RectangleShape &console,
    sf::RectangleShape &text_field
)
{
    translucent_background.setPosition(0, 0);
    translucent_background.setFillColor(sf::Color(0, 25, 0, 100));

    console.setPosition(320.f, 180.f);
    console.setFillColor(sf::Color(0, 0, 0));
    console.setOutlineColor(sf::Color::White);
    console.setOutlineThickness(-1.f);

    text_field.setPosition(350.f, 340.f);
    text_field.setFillColor(sf::Color::White);
}

/**
 * @throw std::runtime_error si la data necesaria no fue encontrada
 */
void initialize_words(std::string *array_words)
{
    std::ifstream file{ R"(data\words.txt)" };

    if (!file)
    {
        throw std::runtime_error{ "Words could not be initialized." };
    }

    std::string word{};
    for (int i{0}; std::getline(file, word); ++i)
    {
        array_words[i] = word;
    }
}

/**
 * @throw std::runtime_error si la data necesaria no fue encontrada
 */
void initialize_companies_with_network(TablaHash<Company*> &companies, GrafoSimple<Node*> &company_network)
{
    std::ifstream file{ R"(data\company_names.txt)" };

    if (!file)
    {
        throw std::runtime_error{ "Company names could not be initialized." };
    }

    std::string name{};
    for (int i{0}; std::getline(file, name); ++i)
    {
        companies.insert(name, new Company{});
        company_network.set_node(i, new Node{ name });
    }

    file.close();

    file.open(R"(data\coordinates.txt)");

    if (!file)
    {
        throw std::runtime_error{ "Coordinates could not be initialized." };
    }

    float x{};
    float y{};
    for (int i{0}; file >> x >> y; ++i)
    {
        company_network.get_element(i)->get_circle().setPosition(x, y);
    }

    company_network.update_edge(0, 5, true);
    company_network.update_edge(0, 1, true);
    company_network.update_edge(1, 4, true);
    company_network.update_edge(2, 6, true);
    company_network.update_edge(2, 7, true);
    company_network.update_edge(2, 8, true);
    company_network.update_edge(3, 4, true);
    company_network.update_edge(3, 9, true);
    company_network.update_edge(3, 10, true);
    company_network.update_edge(4, 5, true);
    company_network.update_edge(5, 6, true);
    company_network.update_edge(6, 7, true);
    company_network.update_edge(6, 12, true);
    company_network.update_edge(7, 8, true);
    company_network.update_edge(8, 20, true);
    company_network.update_edge(9, 10, true);
    company_network.update_edge(9, 11, true);
    company_network.update_edge(10, 13, true);
    company_network.update_edge(11, 12, true);
    company_network.update_edge(11, 14, true);
    company_network.update_edge(12, 15, true);
    company_network.update_edge(13, 16, true);
    company_network.update_edge(13, 17, true);
    company_network.update_edge(16, 17, true);
    company_network.update_edge(17, 18, true);
    company_network.update_edge(17, 21, true);
    company_network.update_edge(21, 18, true);
    company_network.update_edge(21, 20, true);
    company_network.update_edge(14, 15, true);
    company_network.update_edge(14, 19, true);
    company_network.update_edge(15, 19, true);
    company_network.update_edge(20, 19, true);

    for (int i{0}; i < 4; ++i)
    {
        Node *initial_node{ company_network.get_element(select::from_range(0, 21)) };
        initial_node->get_circle().setFillColor(sf::Color::White);

        initial_node->set_status_available(true);
    }
}

/**
 * @throw std::runtime_error si el asset necesario no fue encontrado
 */
void initialize_coins
(
    int yuca_quantity,
    sf::Font &font,
    sf::Text &coin_text,
    sf::CircleShape &circle_coin_container,
    sf::Texture &coin_texture
)
{
    if (!coin_texture.loadFromFile(R"(assets\images\yuca_coin.png)"))
    {
        throw std::runtime_error{ "The coin texture could not be loaded." };
    }

    circle_coin_container.setTexture( &coin_texture );
    circle_coin_container.setRadius(28.f);
    circle_coin_container.setPosition(1190.f, 630.f);
    
    coin_text.setFont(font);
    coin_text.setCharacterSize(45);
    coin_text.setFillColor(sf::Color::White);

    coin_text.setString( std::to_string(yuca_quantity) );
    coin_text.setPosition( 1168 - (coin_text.getGlobalBounds().width / 2), 628.f );

}

/**
 * @throw std::runtime_error si el asset necesario no fue encontrado
 */
void initialize_anonymity
(
    int anonymity,
    sf::Sprite &anonymity_sprite,
    sf::Texture &anonymity_texture
)
{
    if (!anonymity_texture.loadFromFile(R"(assets\images\anonymity_texture.png)"))
    {
        throw std::runtime_error{ "The anonymity texture could not be loaded." };
    }

    anonymity_sprite.setTexture( anonymity_texture );
    anonymity_sprite.setScale(0.35f, 0.35f);
    anonymity_sprite.setTextureRect(sf::IntRect(0, 0, 240, 196));
    anonymity_sprite.setPosition(1166.f, 25.f);
}