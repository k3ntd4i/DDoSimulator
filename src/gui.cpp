#include "../include/gui.hpp"

void draw_bar(sf::RenderWindow &window, sf::Text &progress_bar_text) 
{
    int infected{ 0 };

    progress_bar_text.setString( std::to_string(infected) + " / 22" );
    progress_bar_text.setPosition(640 - (progress_bar_text.getGlobalBounds().width / 2), 598.f);

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
        window.draw(progress_bar_text);
    }
}

void popup_console_window
(
    const std::string &user_input,
    const std::string &command_required,
    sf::Text &command_required_text,
    sf::Text &input_command_text
)
{
    // Palabras random
    command_required_text.setString(command_required);
    command_required_text.setPosition(640 - (command_required_text.getGlobalBounds().width / 2), 270.f);

    input_command_text.setString(user_input);
    input_command_text.setPosition(640 - (input_command_text.getGlobalBounds().width / 2), 335.f);
}