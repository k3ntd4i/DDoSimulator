#pragma once

class Gameplay
{
    int company_counter{ 0 };
    int quantity_words{ 9 };
    bool hard{ false };
    bool extreme{ false };
    float console_time_limit{ 12.f };

public:
    Gameplay() = default;

    int get_company_counter() { return company_counter; }
    int get_quantity_words() { return quantity_words; }
    int get_hard() { return hard; }
    int get_extreme() { return extreme; }
    float get_console_time_limit() { return console_time_limit; }
    void decrease_quantity_words() { --quantity_words; }
    void set_console_time_limit(float new_time) { this->console_time_limit = new_time; }

    void increase_company_counter()
    {
        ++this->company_counter;

        if (this->company_counter == 6) { this->hard = true; }
        if (this->company_counter == 16) { this->extreme = true; }
    }
};