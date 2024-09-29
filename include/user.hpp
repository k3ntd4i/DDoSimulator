#pragma once

class User
{
    int anonymity{ 5 };
    int yuca_coins{ 0 };
    int hack_intensity{ 50 };
    int indirect_hack_intensity{ 25 };
    bool captured{ false };

public:
    User() = default;

    int get_anonymity() { return anonymity; }
    int get_yuca_coins() { return yuca_coins; }
    int get_hack_intensity() { return hack_intensity; }
    int get_indirect_hack_intensity() { return indirect_hack_intensity; }
    bool was_captured() { return captured; }
    void increase_hack_intensity(int new_intesity) { this->hack_intensity += new_intesity; }

    void increase_indirect_hack_intensity(int new_intesity)
    {
        this->indirect_hack_intensity += new_intesity;
    }

    void update_yuca_coins_wallet(int cash_flow) { this->yuca_coins += cash_flow; }

    void decrease_anonymity()
    {
        --this->anonymity;

        if (this->anonymity < 0)
        {
            this->anonymity = 0;
            return;
        }

        if (this->anonymity == 0) { this->captured = true; }
    }
};