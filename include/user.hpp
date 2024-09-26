#pragma once

class User
{
    int anonymity{ 5 };
    int yukacoins{ 0 };
    int hack_intensity{ 10 };
    bool captured{ false };

public:
    User() = default;

    int get_anonymity() { return this->anonymity; }
    int get_yukacoins() { return this->yukacoins; }
    int get_hack_intensity() { return this->hack_intensity; }
    bool was_captured() { return this->captured; }
    void increase_hack_intensity(int new_intesity) { this->hack_intensity += new_intesity; }
    void update_yukacoins_wallet(int cash_flow) { this->yukacoins += cash_flow; }

    void decrease_anonymity()
    {
        --this->anonymity;
        if (this->anonymity == 0) { this->captured = true; }
    }
};