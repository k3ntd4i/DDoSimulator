#pragma once

class CompanyCounter
{
    int counter{ 0 };

public:
    CompanyCounter() = default;

    void increase_counter() { ++counter; }
    int get_counter() { return counter; }
};