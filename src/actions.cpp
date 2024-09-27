#include "../include/actions.hpp"

void verify_node_click
(
    sf::RenderWindow &window,
    GrafoSimple<Node*> &company_network,
    bool &click_flag,
    sf::Clock &console_time,
    int &company_index
)
{
    sf::Vector2i mousePos{ sf::Mouse::getPosition(window) };
    for (int i{0}; i < 22; ++i)
    {
        if (company_network.get_element(i)->get_circle().getGlobalBounds().contains
            (static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))

            && company_network.get_element(i)->is_available()
        )
        {
            std::cout << "Circle " << i + 1 << " clicked\n";
            company_index = i;
            click_flag = true;
            console_time.restart();
        }
    }
}

void clear_conditional_objects
(
    Cola<std::string> &extracted_words,
    bool &click_flag,
    std::string &user_input,
    int &company_index
)
{
    while (!extracted_words.is_empty())
    {
        extracted_words.pop();
    }

    click_flag = false;
    user_input = "";
    company_index = -1;
}

void user_fails_attack
(
    User &user,
    GrafoSimple<Node*> &company_network,
    int company_index
)
{
    user.decrease_anonymity();
    if (user.was_captured())
    {
        std::cout << "\nHA SIDO CAPTURADO BRO, RIP!!!11\n";
    }

    Node *node{ company_network.get_element(company_index) };

    node->set_attack_result(false);

    node->get_circle().setOutlineThickness(0);
    node->get_circle().setFillColor(sf::Color::Red);
    node->set_was_just_attacked(true);
    node->set_status_available(false);
    node->reset_clock();
}

void user_succeeds_attack
(
    User &user,
    GrafoSimple<Node*> &company_network,
    TablaHash<Company*> &companies,
    Gameplay &gameplay_status,
    int company_index
)
{
    Node *node{ company_network.get_element(company_index) };

    Company *company{ companies.search(node->get_company_name()) };
    company->update_integrity(user.get_hack_intensity(), gameplay_status);

    if (gameplay_status.get_company_counter() == 22)
    {
        std::cout << "\nHAS HACKEADO EL PLANETA BRO, EPIC WIN!!!!111\n";
    }

    user.update_yuca_coins_wallet(6);

    node->set_attack_result(true);
    node->set_status_infected(!company->is_active());

    node->get_circle().setOutlineColor(sf::Color{ 0, 190, 0 });
    node->set_was_just_attacked(true);
    node->set_status_available(false);
    node->reset_clock();
}