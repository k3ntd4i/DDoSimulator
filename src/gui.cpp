#include "../include/gui.hpp"

void draw_bar(sf::RenderWindow &window, sf::Text &progress_bar_text, Gameplay &gameplay_status)
{
    int infected{ gameplay_status.get_company_counter() };

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
    sf::Text &input_command_text,
    sf::Clock &console_time,
    sf::RectangleShape &time_bar
)
{
    Lista<std::string> words{};
    std::string build_word{};
    int index_insert{0};

    for (int i = 0; i <= command_required.length(); ++i)
    {
        if (i == command_required.length() || command_required[i] == ' ')
        {
            words.insert(index_insert, build_word);
            build_word.clear();
            ++index_insert;
        }
        else
        {
            build_word += command_required[i];
        }
    }

    float text_heigth{ 325.f };
    int temporal_space_index{ 0 };
    std::string command_required_copy{};

    for (int i{0}; i < words.size(); ++i)
    {
        command_required_copy += words.get(i);
        command_required_text.setString(command_required_copy);

        if (command_required_text.getGlobalBounds().width >= 580.f)
        {
            command_required_copy[command_required_copy.find_last_of(' ')] = '\n';
            text_heigth -= 40;
        }

        command_required_copy += ' ';
    }
    

    
    float elapsed_time{console_time.getElapsedTime().asSeconds()};
    if (elapsed_time < 3.5f) 
    {
        time_bar.setFillColor(sf::Color::Green);
        time_bar.setSize(sf::Vector2f{638.f, 7.f});
    }
    else if (elapsed_time >= 3.5f && elapsed_time < 7.f) 
    {
        time_bar.setFillColor(sf::Color::Yellow);
        time_bar.setSize(sf::Vector2f{478.f, 7.f});
    }
    else if (elapsed_time >= 7.f && elapsed_time <= 10.5f)
    {
        time_bar.setFillColor(sf::Color(255,131,0));
        time_bar.setSize(sf::Vector2f{319.f, 7.f});
    }
    else if (elapsed_time >= 10.5f && elapsed_time < 12.f)
    {
        time_bar.setFillColor(sf::Color::Red);
        time_bar.setSize(sf::Vector2f{159.f, 7.f});
    }
    else if (elapsed_time >= 12.f && elapsed_time < 13.5f)
    {
        time_bar.setFillColor(sf::Color::Red);
        time_bar.setSize(sf::Vector2f{40.f, 7.f});
    }
    else if (elapsed_time >= 13.5f)
    {
        time_bar.setFillColor(sf::Color::Red);
        time_bar.setSize(sf::Vector2f{6.f, 7.f});
    }

    time_bar.setPosition(640 - (time_bar.getGlobalBounds().width / 2), 532.f);

    command_required_text.setString(command_required_copy);
    command_required_text.setPosition(640 - (command_required_text.getGlobalBounds().width / 2), text_heigth);

    input_command_text.setString(user_input);
    input_command_text.setPosition(640 - (input_command_text.getGlobalBounds().width / 2), 390.f);
}