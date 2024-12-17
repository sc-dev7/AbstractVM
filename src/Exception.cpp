/*
** EPITECH PROJECT, 2024
** SYNTHESE
** File description:
** sc
*/

#include "../include/Exception.hpp"

vm::Exception::Exception(const std::string &message, const std::string &where) : _where(where), _message(message)
{
}

const std::string &vm::Exception::Exception::where() const
{
    return _where;
}

const char *vm::Exception::what() const noexcept
{
    return _message.c_str();
}
