/*
** EPITECH PROJECT, 2024
** SYNTHESE
** File description:
** sc
*/

#include "../include/Abstract.hpp"
#include "../include/Exception.hpp"
#include "../include/Factory.hpp"
#include "../include/IOperand.hpp"
#include <list>
#include <regex>

AbstractVM::AbstractVM()
{
    _line = 0;
    _size_stack = 0;
}

AbstractVM::~AbstractVM()
{
}

int AbstractVM::runInstruction(const std::string &command, IOperand *operand)
{
    void (AbstractVM::*func)(IOperand *) = _intructions[command];
    (this->*func)(operand);
    return 0;
}

std::string trim(const std::string &str)
{
    std::string::const_iterator i = str.begin();

    while (i != str.end() && isspace(*i))
        i++;

    std::string::const_reverse_iterator rev_i = str.rbegin();

    while (rev_i.base() != i && isspace(*rev_i))
        rev_i++;
    return std::string(i, rev_i.base());
}

int AbstractVM::shell()
{
    while (1) {
        std::string input;
        std::getline(std::cin, input);
        if (input.empty()) {
            continue;
        }
        if (input == ";;") {
            break;
        }
        parse_line(input);
    }
    return 0;
}

eOperandType getOperandType(const std::string stype)
{
    if (stype == "int8")
        return Int8;
    if (stype == "int16")
        return Int16;
    if (stype == "int32")
        return Int32;
    if (stype == "float")
        return Float;
    if (stype == "double")
        return Double;
    throw vm::Exception("Unknown stype" + stype);
    return Int8;
}

int AbstractVM::parse_line(string line)
{
    std::regex simple(R"(^\s*(pop|dump|clear|dup|swap|add|sub|mul|div|mod|print|exit)\s*$)");
    std::regex withInt(R"(^\s*(push|assert|load|store)\s+(int8|int16|int32|bigdecimal)\s*\(\s*(-?\d+)\s*\)\s*$)");
    std::regex withValue(R"(^\s*(push|assert|load|store)\s+(float|double|bigdecimal)\s*\(\s*(-?\d+\.\d+)\s*\)\s*$)");
    std::smatch matches;
    line = trim(line);

    if (line[0] == '\0') {
        return 0;
    }
    if (line.empty() or line.at(0) == ';')
        return (false);
    if (regex_search(line, matches, withInt))
        return runInstruction(matches.str(1), Factory::createOperand(getOperandType(matches.str(2)), matches.str(3)));
    if (regex_search(line, matches, withValue))
        return runInstruction(matches.str(1), Factory::createOperand(getOperandType(matches.str(2)), matches.str(3)));
    else if (regex_search(line, matches, simple))
        return runInstruction(matches.str(1), nullptr);
    else
        throw vm::Exception("invalid instruction '" + line + "'.");
    return 0;
}

int AbstractVM::parse(const std::string &filename)
{
    ifstream file(filename);

    if (file) {
        string line;
        while (getline(file, line)) {
            _line++;
            parse_line(line);
        }
        throw vm::Exception("exit");
    }
    else
        throw vm::Exception("Error opening file.");
    return 0;
}

void AbstractVM::push(IOperand *operand)
{
    _size_stack++;
    _stack.push_front(operand);
}

void AbstractVM::pop(IOperand *operand)
{
    (void)operand;

    if (_size_stack == 0)
        throw vm::Exception("Stack empty");

    operand = _stack.front();

    _size_stack--;
    _stack.pop_front();
}

void AbstractVM::dump(IOperand *operand)
{
    (void)operand;

    if (_size_stack == 0)
        throw vm::Exception("Stack empty");

    list<IOperand *>::iterator i;
    for (i = _stack.begin(); i != _stack.end(); ++i)
        std::cout << (*i)->toString() << std::endl;
}

void AbstractVM::clear(IOperand *operand)
{
    for (int i = 0; i < _size_stack; i++) {
        pop(operand);
    }
}

void AbstractVM::dup(IOperand *operand)
{
    (void)operand;

    if (_size_stack == 0)
        throw vm::Exception("Dup need 1 value");

    IOperand *op1 = _stack.front();
    IOperand *op2 = Factory::createOperand(op1->getType(), op1->toString());
    push(op2);
}

void AbstractVM::swap(IOperand *operand)
{
    (void)operand;

    if (_size_stack < 2)
        throw vm::Exception("Swap need 2 values");

    IOperand *op1 = _stack.front();
    pop(op1);
    IOperand *op2 = _stack.front();
    pop(op2);
    push(op2);
    push(op1);
}

void AbstractVM::assert_vm(IOperand *operand)
{
    if (_size_stack == 0)
        throw vm::Exception("Stack empty");

    IOperand *op1 = _stack.front();

    if (op1->getType() != operand->getType())
        throw vm::Exception("Assert different type");
    if (op1->getType() < Float) {
        if (std::stoll(op1->toString()) != std::stoll(operand->toString()))
            throw vm::Exception("Assert different value");
    }
    else {
        if (std::stold(op1->toString()) != std::stold(operand->toString()))
            throw vm::Exception("Assert different type");
    }
}

void AbstractVM::add(IOperand *operand)
{
    (void)operand;

    if (_size_stack < 2)
        throw vm::Exception("Add need 2 values");

    IOperand *op1 = _stack.front();
    pop(op1);
    IOperand *op2 = _stack.front();
    pop(op2);
    IOperand *res = *op1 + *op2;
    push(res);
}

void AbstractVM::sub(IOperand *operand)
{
    (void)operand;

    if (_stack.size() < 2)
        throw vm::Exception("Sub need 2 values");
    IOperand *op1 = _stack.front();
    _stack.pop_front();
    IOperand *op2 = _stack.front();
    _stack.pop_front();
    IOperand *res = *op2 - *op1;
    _stack.push_front(res);
    delete op1;
    delete op2;
}

void AbstractVM::mul(IOperand *operand)
{
    (void)operand;

    if (_size_stack < 2)
        throw vm::Exception("Mul need 2 values");

    IOperand *op1 = _stack.front();
    pop(op1);
    IOperand *op2 = _stack.front();
    pop(op2);
    IOperand *res = *op1 * *op2;
    push(res);
}

void AbstractVM::div(IOperand *operand)
{
    (void)operand;

    if (_size_stack < 2)
        throw vm::Exception("Div need 2 values");

    IOperand *op1 = _stack.front();
    pop(op1);
    IOperand *op2 = _stack.front();

    if (op2->toString() == "0")
        throw vm::Exception("Div by zero");

    pop(op2);
    IOperand *res = *op1 / *op2;
    push(res);
}

void AbstractVM::mod(IOperand *operand)
{
    (void)operand;

    if (_size_stack < 2)
        throw vm::Exception("Mod need 2 values");

    IOperand *op1 = _stack.front();
    pop(op1);
    IOperand *op2 = _stack.front();

    if (op2->toString() == "0")
        throw vm::Exception("Mod by zero");

    pop(op2);
    IOperand *res = *op1 % *op2;
    push(res);
}

void AbstractVM::load(IOperand *operand)
{
    (void)operand;

    if (_size_stack == 0 || operand == nullptr) {
        throw vm::Exception("Cannot load: stack is empty or invalid operand.");
    }

    int index = std::stoi(operand->toString());

    if (index < 0 || index >= _size_stack) {
        throw vm::Exception("Invalid index for load command.");
    }

    IOperand *toLoad = _stack.front();
    auto it = _stack.begin();
    std::advance(it, index);
    toLoad = *it;

    _stack.push_front(toLoad);
    _size_stack++;
}

void AbstractVM::store(IOperand *operand)
{
    (void)operand;

    if (_size_stack == 0 || operand == nullptr) {
        throw vm::Exception("Cannot store: stack is empty or invalid operand.");
    }

    int index = std::stoi(operand->toString());

    if (index < 0 || index >= _size_stack) {
        throw vm::Exception("Invalid index for store command.");
    }

    IOperand *toStore = _stack.front();
    auto it = _stack.begin();
    std::advance(it, index);

    delete *it;
    *it = toStore;

    _stack.pop_front();
    _size_stack--;
}

void AbstractVM::print(IOperand *operand)
{
    (void)operand;

    if (_size_stack == 0)
        throw vm::Exception("Print stack empty");

    const IOperand *op1 = *(_stack.begin());

    if (op1->getType() != Int8)
        throw vm::Exception("Print not int8");
    std::cout << static_cast<char>(std::stoi(op1->toString())) << std::endl;
}

void AbstractVM::exit_VM(IOperand *operand)
{
    (void)operand;

    exit(0);
}
