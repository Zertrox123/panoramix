##
## EPITECH PROJECT, 2024
## omar
## File description:
## Makefile
##

SRC	=	src/main.c	\
		src/druid.c	\
		src/village.c	\

OBJ = $(SRC:.c=.o)

CFLAGS = -g3 -I./include -Wno-deprecated-declarations

NAME = panoramix

$(NAME):	$(OBJ)
		clang -o $(NAME) $(OBJ) $(CFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f *.gcno
	rm -f *.gcda
	rm -f unit_tests

re: fclean all
