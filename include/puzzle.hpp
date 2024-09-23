#pragma once

#include "../include/estructuras/cola.hpp"
#include "../include/random.hpp"
#include <iostream>
#include <string>
#include <string_view>

std::string get_command(int amount, Cola<std::string> &extracted_words, bool hard = false);
bool correct_command(std::string_view input_command, Cola<std::string> &extracted_words);