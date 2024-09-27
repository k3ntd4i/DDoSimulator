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
void initialize_companies_and_network(TablaHash<Company*> &companies, GrafoSimple<Node*> &company_network)
{
    std::ifstream file_names{ R"(data\company_names.txt)" };

    if (!file_names)
    {
        throw std::runtime_error{ "Company names could not be initialized." };
    }

    std::ifstream file_graph{ R"(data\coordinates.txt)" };

    if (!file_graph)
    {
        throw std::runtime_error{ "Coordinates could not be initialized." };
    }

    float x{};
    float y{};
    std::string name{};
    for (int i{0}; i < 22; ++i)
    {
        std::getline(file_names, name);
        file_graph >> x >> y;

        companies.insert(name, new Company{});
        company_network.set_node(i, new Node{ name });
        company_network.get_element(i)->get_circle().setPosition(x, y);
    }

    file_graph.close();
    file_graph.open( R"(data\graph_edges.txt)" );

    if (!file_graph)
    {
        throw std::runtime_error{ "The edges of the graph could not be initialized." };
    }

    for (int i{0}; file_graph >> x >> y; ++i)
    {
        company_network.update_edge(x, y, true);
    }

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
void initialize_anonymity(int anonymity, sf::Sprite &anonymity_sprite, sf::Texture &anonymity_texture)
{
    if (!anonymity_texture.loadFromFile(R"(assets\images\anonymity_texture.png)"))
    {
        throw std::runtime_error{ "The anonymity texture could not be loaded." };
    }

    anonymity_sprite.setTexture( anonymity_texture );
    anonymity_sprite.setScale(0.35f, 0.35f);
    anonymity_sprite.setTextureRect(sf::IntRect(240 * anonymity, 0, 240, 196));
    anonymity_sprite.setPosition(1166.f, 25.f);
}