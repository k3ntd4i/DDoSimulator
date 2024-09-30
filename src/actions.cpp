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
            std::cout << "\nCircle " << i + 1 << " clicked\n";
            company_index = i;
            click_flag = true;
            console_time.restart();
            break;
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
    sf::Sprite &anonymity_sprite,
    GrafoSimple<Node*> &company_network,
    int company_index
)
{
    user.decrease_anonymity();
    anonymity_sprite.setTextureRect(sf::IntRect(240 * user.get_anonymity(), 0, 240, 196));

    if (user.was_captured())
    {
        std::cout << "\nHA SIDO CAPTURADO BRO, RIP!!!11\n";
    }

    Node *node{ company_network.get_element(company_index) };

    node->get_circle().setOutlineColor(sf::Color::Red);
    node->get_circle().setFillColor(sf::Color::Red);
    node->set_was_just_attacked(true);
    node->set_status_available(false);
    node->reset_clock();
}

void user_succeeds_attack
(
    User &user,
    sf::Text &coin_text,
    GrafoSimple<Node*> &company_network,
    TablaHash<Company*> &companies,
    Gameplay &gameplay_status,
    int company_index
)
{
    Node *node{ company_network.get_element(company_index) };

    Company *company{ companies.search(node->get_company_name()) };
    company->update_integrity(user.get_hack_intensity(), gameplay_status);

    Lista<Node*> *adjacent_nodes{ company_network.get_adjacent_nodes(company_index) };

    int quantity_adjacent_nodes{ adjacent_nodes->size() };
    for (int i{0}; i <= quantity_adjacent_nodes; ++i)
    {
        if (!company->is_active() && !node->is_infected())
        {
            user.update_yuca_coins_wallet(6);
            coin_text.setString( std::to_string(user.get_yuca_coins()) );
            coin_text.setPosition(1155.f - (coin_text.getGlobalBounds().width / 2.f), 628.f);
            node->set_status_infected(!company->is_active());
        }

        if (gameplay_status.get_company_counter() == 22)
        {
            std::cout << "\nHAS HACKEADO EL PLANETA BRO, EPIC WIN!!!!111\n";
        }

        node->get_circle().setOutlineColor(sf::Color{ 0, 162, 232 });

        if (i > 0)
        {
            node->get_circle().setFillColor(sf::Color::White);
            node->set_status_available(true);
        }
        else
        {
            node->get_circle().setFillColor(sf::Color{ 0, 162, 232 });
            node->set_status_available(false);
        }

        node->set_was_just_attacked(true);
        node->reset_clock();

        if (i == quantity_adjacent_nodes)
        {
            break;
        }

        node = adjacent_nodes->get(i);

        company = companies.search(node->get_company_name());
        company->update_integrity(user.get_indirect_hack_intensity(), gameplay_status);
    }

    delete adjacent_nodes;
}