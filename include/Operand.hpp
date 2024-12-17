/*
** EPITECH PROJECT, 2024
** SYNTHESE
** File description:
** sc
*/

#include "Exception.hpp"
#include "Factory.hpp"
#include "IOperand.hpp"
#include <sstream>

class Operand : public IOperand {
    public:
        Operand();
        Operand(const std::string &value);

        std::string toString() const override;
        eOperandType getType() const override;

        IOperand *operator+(const IOperand &rhs) const override;
        IOperand *operator-(const IOperand &rhs) const override;
        IOperand *operator*(const IOperand &rhs) const override;
        IOperand *operator/(const IOperand &rhs) const override;
        IOperand *operator%(const IOperand &rhs) const override;

    protected:
        std::string _str;
        eOperandType _type;
        int _precision;
};

class CInt8 : public Operand {
    public:
        CInt8();
        CInt8(const std::string &value);
};

class CInt16 : public Operand {
    public:
        CInt16();
        CInt16(const std::string &value);
};

class CInt32 : public Operand {
    public:
        CInt32();
        CInt32(const std::string &value);
};

class CFloat : public Operand {
    public:
        CFloat();
        CFloat(const std::string &value);
};

class CDouble : public Operand {
    public:
        CDouble();
        CDouble(const std::string &value);
};
