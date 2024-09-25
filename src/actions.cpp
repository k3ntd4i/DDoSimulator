#include "../include/actions.hpp"

void verify_node_click(sf::RenderWindow &window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Logica temporal para clickear los nodos de las compañias
    for (int i = 0; i < 5; ++i)
    {
        if (circles[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) 
        {
            circles[i].setFillColor(sf::Color::Red);
            std::cout << "Circle " << i + 1 << " clicked\n";
            click_flag = true;
            console_time.restart();
        }
    }
}