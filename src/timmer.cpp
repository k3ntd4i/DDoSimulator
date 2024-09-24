#include "../include/timmer.hpp"


void draw_countdown(sf::RenderWindow &window, sf::Clock &clock, sf::Time &countdown_time, sf::Text &countdown_text)
{

    sf::Time elapsed_time = clock.getElapsedTime();
    sf::Time time_remaining{countdown_time - elapsed_time};

    if (time_remaining.asSeconds() <= 0) {
        time_remaining = sf::seconds(0);
    }


    sf::FloatRect textBounds{countdown_text.getGlobalBounds()};
    float width{textBounds.width};
    countdown_text.setPosition(640.f - (width/2.f), 15.f);


    countdown_text.setString(std::to_string(static_cast<int>(time_remaining.asSeconds())));


    window.draw(countdown_text);
}