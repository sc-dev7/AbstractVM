/*
** EPITECH PROJECT, 2024
** SYNTHESE
** File description:
** sc
*/

#include "../include/Factory.hpp"
#include "../include/IOperand.hpp"
#include "../include/Operand.hpp"

Factory::Factory()
{
    _operands[Int8] = &Factory::createInt8;
    _operands[Int16] = &Factory::createInt16;
    _operands[Int32] = &Factory::createInt32;
    _operands[Float] = &Factory::createFloat;
    _operands[Double] = &Factory::createDouble;
}

Factory::~Factory()
{
}

Factory &Factory::getInstance() {
    static Factory instance;
    return instance;
}

IOperand *Factory::createOperand(eOperandType type, const std::string &value) {
    Factory &instance = Factory::getInstance();
    auto it = instance._operands.find(type);
    if (it != instance._operands.end()) {
        return (instance.*(it->second))(value);
    }
    return nullptr;
}

IOperand *Factory::createInt8(const std::string &value)
{
    CInt8 *op = new CInt8(value);
    IOperand *Iop = op;
    return Iop;
}

IOperand *Factory::createInt16(const std::string &value)
{
    CInt16 *op = new CInt16(value);
    IOperand *Iop = op;
    return Iop;
}

IOperand *Factory::createInt32(const std::string &value)
{
    CInt32 *op = new CInt32(value);
    IOperand *Iop = op;
    return Iop;
}

IOperand *Factory::createFloat(const std::string &value)
{
    CFloat *op = new CFloat(value);
    IOperand *Iop = op;
    return Iop;
}

IOperand *Factory::createDouble(const std::string &value)
{
    CDouble *op = new CDouble(value);
    IOperand *Iop = op;
    return Iop;
}
