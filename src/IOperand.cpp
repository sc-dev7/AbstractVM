/*
** EPITECH PROJECT, 2024
** SYNTHESE
** File description:
** sc
*/

#include "../include/Abstract.hpp"

int main(int ac, char **av)
{
    AbstractVM vm;

    try {
        if (ac == 2) {
            return vm.parse(av[1]);
        }
        if (ac == 1)
            return vm.shell();
        else
            throw vm::Exception("Error open file.");
    }
    catch (vm::Exception &err) {
        std::cerr << err.what() << std::endl;
        return (84);
    }
    return 0;
}
