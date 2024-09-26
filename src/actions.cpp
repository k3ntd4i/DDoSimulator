#include "../include/actions.hpp"

void verify_node_click
(
    sf::RenderWindow &window,
    GrafoSimple<sf::CircleShape*> &company_network,
    bool &click_flag,
    sf::Clock &console_time
)
{
    sf::Vector2i mousePos{ sf::Mouse::getPosition(window) };
    for (int i{0}; i < 5; ++i)
    {
        if (company_network.get_element(i)->getGlobalBounds().contains
            (static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            company_network.get_element(i)->setFillColor(sf::Color::Red);
            std::cout << "Circle " << i + 1 << " clicked\n";
            click_flag = true;
            console_time.restart();
        }
    }
}