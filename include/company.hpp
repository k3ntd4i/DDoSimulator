#pragma once

#include "../include/company_counter.hpp"
#include <string>
#include <string_view>

class Company
{
    std::string name{};
    int integriy{};
    bool active{};

public:
    Company(const std::string &new_name)
        : name{ new_name }
        , integriy{ 100 }
        , active{ true }
    {
    }

    void update_integrity(int damage, CompanyCounter &company_counter);

    std::string_view get_name() { return this->name; }
    int get_integrity() { return this->integriy; }
    bool is_active() { return this->active; }
};