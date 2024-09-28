#include "../include/timmer.hpp"

void draw_countdown
(
    sf::RenderWindow &window,
    sf::Clock &clock,
    sf::Time &countdown_time,
    sf::Text &countdown_text
)
{
    sf::Time time_remaining{ countdown_time - clock.getElapsedTime() };

    if (time_remaining.asSeconds() <= 0)
    {
        time_remaining = sf::seconds(0);
    }

    countdown_text.setPosition(640.f - (countdown_text.getGlobalBounds().width / 2.f), 10.f);
    countdown_text.setString(std::to_string(static_cast<int>(time_remaining.asSeconds())));

    window.draw(countdown_text);
}