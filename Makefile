##
## EPITECH PROJECT, 2023
## B-SYN-400-MAR-4-1-abstractVM-oscar.samoun
## File description:
## Makefile
##

SRC =   src/*.cpp

OBJ	=	$(SRC:.o)

NAME =    abstractVM

all:    $(NAME)

$(NAME):	$(OBJ)
	g++ -std=c++20 -Wall -Wextra -Werror -o $(NAME) $(SRC)
	rm -f *.o

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
