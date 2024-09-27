#pragma once

class Gameplay
{
    int company_counter{ 0 };
    int amount_words{ 3 };
    bool hard{ false };
    bool extreme{ false };

public:
    Gameplay() = default;

    int get_company_counter() { return company_counter; }
    int get_amount_words() { return amount_words; }
    int get_hard() { return hard; }
    int get_extreme() { return extreme; }
    void increase_company_counter() { ++company_counter; }
};