#include "../include/puzzle.hpp"

std::string get_command
(
    int amount,
    Cola<std::string> &queue_words,
    std::string *words,
    bool hard,
    bool extreme
)
{
    static const std::string chars[] {"!", "#", "$", "%", "&", "/", "(", ")", "=", "?"};

    queue_words.push(words[select::from_range(0, 1999)]);

    std::string command_required{ queue_words.back() };
    for (int i{1}; i < amount; ++i)
    {
        queue_words.push(words[select::from_range(0, 1999)]);
        command_required += " " + queue_words.back();

        if (hard && select::from_range(0, 1))
        {
            queue_words.push(std::to_string(select::from_range(0, 9)));
            command_required += " " + queue_words.back();
        }

        if (extreme && select::from_range(0, 1))
        {
            queue_words.push(chars[select::from_range(0, 9)]);
            command_required += " " + queue_words.back();
        }
    }

    return command_required;
}

bool correct_command(std::string_view input_command, Cola<std::string> &extracted_words)
{
    if (input_command.size() != extracted_words.size())
    {
        return false;
    }

    for (int i{0}; i < input_command.size(); ++i)
    {
        if (input_command[i] != extracted_words.pop()[0])
        {
            return false;
        }
    }

    return true;
}
