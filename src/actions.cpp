#include "../include/actions.hpp"

void verify_node_click
(
    sf::RenderWindow &window,
    GrafoSimple<Node*> &company_network,
    bool &click_flag,
    sf::Clock &console_time
)
{
    sf::Vector2i mousePos{ sf::Mouse::getPosition(window) };
    for (int i{0}; i < 22; ++i)
    {
        if (company_network.get_element(i)->get_circle().getGlobalBounds().contains
            (static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))
            && company_network.get_element(i)->is_available())
        {
            std::cout << "Circle " << i + 1 << " clicked\n";
            click_flag = true;
            console_time.restart();
        }
    }
}

void clear_conditional_objects
(
    Cola<std::string> &extracted_words,
    bool &click_flag,
    std::string &user_input
)
{
    while (!extracted_words.is_empty())
    {
        extracted_words.pop();
    }

    click_flag = false;
    user_input = "";
}