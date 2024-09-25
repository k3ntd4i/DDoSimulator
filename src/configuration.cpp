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

void initialize_progress_text(sf::Font &font, sf::Text &text)
{
    if (!font.loadFromFile("./assets/fonts/digital.TTF"))
    {
        throw std::runtime_error{ "The font could not be loaded." };
    }

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
