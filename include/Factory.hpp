/*
** EPITECH PROJECT, 2024
** SYNTHESE
** File description:
** sc
*/

#pragma once

#include "IOperand.hpp"
#include <map>
#include <string>

class Factory {
    public:
        Factory();
        ~Factory();
        static IOperand *createOperand(eOperandType type, const std::string &value);

    private:
        std::map<eOperandType, IOperand *(Factory::*)(const std::string &value)> _operands;
        IOperand *createInt8(const std::string &value);
        IOperand *createInt16(const std::string &value);
        IOperand *createInt32(const std::string &value);
        IOperand *createFloat(const std::string &value);
        IOperand *createDouble(const std::string &value);
        static Factory &getInstance();
};
