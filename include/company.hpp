#pragma once

#include "../include/gameplay.hpp"

class Company
{
    int integriy{};
    bool active{};

public:
    Company()
        : integriy{ 100 }
        , active{ true }
    {
    }

    int get_integrity() { return this->integriy; }
    bool is_active() { return this->active; }

    void update_integrity(int damage, Gameplay &gameplay_status);
};