#include "../include/company.hpp"

void Company::update_integrity(int damage, Gameplay &gameplay_status)
{
    if (!this->active)
    {
        return;
    }

    this->integriy -= damage;

    if (this->integriy <= 0 && this->active)
    {
        gameplay_status.increase_company_counter();
        this->active = false;
    }
}