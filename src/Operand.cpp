/*
** EPITECH PROJECT, 2024
** SYNTHESE
** File description:
** sc
*/

#include "../include/Operand.hpp"

Operand::Operand() : _str(""), _type(Int8), _precision(0) {}

Operand::Operand(const std::string &value) : _str(value), _type(Int8), _precision(0) {
    if (value != "")
        return;
}

std::string Operand::toString() const {
    return _str;
}

eOperandType Operand::getType() const {
    return _type;
}

IOperand *Operand::operator+(const IOperand &rhs) const {
    std::stringstream str_s;
    eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
    if (type < Float) {
        long long res = std::stoll(_str) + std::stoll(rhs.toString());
        str_s << res;
    } else {
        long double res = std::stold(_str) + std::stold(rhs.toString());
        str_s << res;
    }
    return Factory::createOperand(type, str_s.str());
}

IOperand *Operand::operator-(const IOperand &rhs) const {
    std::stringstream str_s;
    eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
    if (type < Float) {
        long long res = std::stoll(_str) - std::stoll(rhs.toString());
        str_s << res;
    } else {
        long double res = std::stold(_str) - std::stold(rhs.toString());
        str_s << res;
    }
    return Factory::createOperand(type, str_s.str());
}

IOperand *Operand::operator*(const IOperand &rhs) const {
    std::stringstream str_s;
    eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
    if (type < Float) {
        long long res = std::stoll(_str) * std::stoll(rhs.toString());
        str_s << res;
    } else {
        long double res = std::stold(_str) * std::stold(rhs.toString());
        str_s << res;
    }
    return Factory::createOperand(type, str_s.str());
}

IOperand *Operand::operator/(const IOperand &rhs) const {
    std::stringstream str_s;
    eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
    if (type < Float) {
        long long res = std::stoll(_str) / std::stoll(rhs.toString());
        str_s << res;
    } else {
        long double res = std::stold(_str) / std::stold(rhs.toString());
        str_s << res;
    }
    return Factory::createOperand(type, str_s.str());
}

IOperand *Operand::operator%(const IOperand &rhs) const {
    std::stringstream str_s;
    eOperandType type = (_type >= rhs.getType()) ? _type : rhs.getType();
    if (type < Float) {
        long long res = std::stoll(_str) % std::stoll(rhs.toString());
        str_s << res;
    } else {
        throw vm::Exception("Mod only on Int");
    }
    return Factory::createOperand(type, str_s.str());
}

CInt8::CInt8(const std::string &value) : Operand(value) {
    _type = Int8;
}

CInt16::CInt16(const std::string &value) : Operand(value) {
    _type = Int16;
}

CInt32::CInt32(const std::string &value) : Operand(value) {
    _type = Int32;
}

CFloat::CFloat(const std::string &value) : Operand(value) {
    _type = Float;
}

CDouble::CDouble(const std::string &value) : Operand(value) {
    _type = Double;
}
