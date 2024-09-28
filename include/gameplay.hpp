#pragma once

class Gameplay
{
    int company_counter{ 0 };
    int quantity_words{ 9 };
    bool hard{ false };
    bool extreme{ false };

public:
    Gameplay() = default;

    int get_company_counter() { return company_counter; }
    int get_quantity_words() { return quantity_words; }
    int get_hard() { return hard; }
    int get_extreme() { return extreme; }
    void increase_company_counter() { ++company_counter; }
};