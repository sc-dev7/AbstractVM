/*
** EPITECH PROJECT, 2024
** SYNTHESE
** File description:
** sc
*/

#pragma once

#include <string>

namespace vm {
    class Exception : public std::exception {
        public:
            Exception(const std::string &message, const std::string &where = "Unknown");
            virtual ~Exception() throw(){};
            const std::string &where() const;
            const char *what() const noexcept override;

        protected:
            std::string _where;

        private:
            std::string _message;
    };
};
