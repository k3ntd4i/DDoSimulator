#pragma once

#include "../include/estructuras/cola.hpp"
#include "../include/random.hpp"
#include <iostream>
#include <string>
#include <string_view>

std::string get_command
(
    int amount,
    Cola<std::string> &extracted_words,
    std::string *words,
    bool hard = false,
    bool extreme = false
);

bool is_input_command_correct(std::string_view input_command, Cola<std::string> &extracted_words);