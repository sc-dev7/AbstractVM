/*
** EPITECH PROJECT, 2024
** SYNTHESE
** File description:
** sc
*/

#pragma once

#include "Exception.hpp"
#include "IOperand.hpp"
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;

class AbstractVM {

    public:
        AbstractVM();
        ~AbstractVM();
        int parse(const std::string &filename);
        int parse_line(string line);
        int shell();
        int run();
        int runInstruction(const std::string &command, IOperand *operand);
        void push(IOperand *operand);
        void pop(IOperand *operand);
        void dump(IOperand *operand);
        void clear(IOperand *operand);
        void dup(IOperand *operand);
        void swap(IOperand *operand);
        void assert_vm(IOperand *operand);
        void add(IOperand *operand);
        void sub(IOperand *operand);
        void mul(IOperand *operand);
        void div(IOperand *operand);
        void mod(IOperand *operand);
        void load(IOperand *operand);
        void store(IOperand *operand);
        void print(IOperand *operand);
        void exit_VM(IOperand *operand);

    private:
        int _line;
        list<IOperand *> _stack;
        int _size_stack = 0;
        std::map<const std::string, void (AbstractVM::*)(IOperand *)> _intructions = {
            {"push", &AbstractVM::push},
            {"pop", &AbstractVM::pop},
            {"dump", &AbstractVM::dump},
            {"clear", &AbstractVM::clear},
            {"dup", &AbstractVM::dup},
            {"swap", &AbstractVM::swap},
            {"assert", &AbstractVM::assert_vm},
            {"add", &AbstractVM::add},
            {"sub", &AbstractVM::sub},
            {"mul", &AbstractVM::mul},
            {"div", &AbstractVM::div},
            {"mod", &AbstractVM::mod},
            {"load", &AbstractVM::load},
            {"store", &AbstractVM::store},
            {"print", &AbstractVM::print},
            {"exit", &AbstractVM::exit_VM}
        };
};
