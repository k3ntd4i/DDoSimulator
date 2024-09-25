#include "../include/company.hpp"

void Company::update_integrity(int damage, CompanyCounter &company_counter)
{
    if (!this->active)
    {
        return;
    }

    this->integriy -= damage;

    if (this->integriy <= 0 && this->active)
    {
        company_counter.increase_counter();
        this->active = false;
    }
}