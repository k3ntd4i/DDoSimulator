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

void initialize_font(sf::Font &font)
{
    if (!font.loadFromFile("./assets/fonts/digital.TTF"))
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
    // text_field.setOutlineColor(sf::Color::White);
    // text_field.setOutlineThickness(-2.f);
}

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

void initialize_company_network(GrafoSimple<sf::CircleShape*> &company_network)
{
    sf::CircleShape *circle{};
    for (int i{0}; i < 5; ++i)
    {
        circle = new sf::CircleShape{};

        circle->setRadius(50);
        circle->setPosition(100 * (i + 5), 200);
        circle->setFillColor(sf::Color::Green);

        company_network.set_node(i, circle);
    }
}
