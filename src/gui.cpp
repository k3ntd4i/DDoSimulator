#include "../include/gui.hpp"

void draw_bar(sf::RenderWindow &window, sf::Text &text) 
{
    int infected{ 10 };

    text.setString( std::to_string(infected) + " / 22" );
    text.setPosition(640 - (text.getGlobalBounds().width / 2), 598.f);

    int square_x_position{ 464 };
    for (int total_squares{0}; total_squares < 22; ++total_squares)
    {
        sf::RectangleShape square{ sf::Vector2f{ 13.f, 37.f } };
        square.setPosition(square_x_position, 639);

        if (infected < 0 || infected > 0)
        {
            square.setFillColor(sf::Color::Red);
            infected -= 1;
        }
        else
        {
            square.setFillColor(sf::Color::Black);
            square.setOutlineColor(sf::Color::Red);
            square.setOutlineThickness(-1.f);
        }

        square_x_position += 17;
        window.draw(square);
        window.draw(text);
    }
}