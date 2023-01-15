##
## EPITECH PROJECT, 2021
## B-NWP-400-NCE-4-1-myftp-victor.sorais
## File description:
## Makefile
##

NAME		=		myftp

SRC			=		$(wildcard src/*.c) \
					main.c \

OBJ			=		$(SRC:.c=.o)

$(NAME):			$(OBJ)
					gcc -o $(NAME) $(OBJ) -g3

all:				$(NAME)

clean:
					rm -f $(OBJ)

fclean:				clean
					rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re