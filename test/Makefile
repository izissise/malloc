##
## Makefile for make me in /home/collin_b/project/malloc/PSU_2013_malloc/debug
## 
## Made by jonathan.collinet
## Login   <collin_b@epitech.net>
## 
## Started on  Mon Feb  3 11:22:47 2014 jonathan.collinet
## Last update Mon Feb  3 17:41:13 2014 jonathan.collinet
##

SRC		=		main.c		\

OBJ		=		$(SRC:.c=.o)

CC		=		gcc -g -L../ -lmy_malloc

NAME		=		debug

all:				$(OBJ)
				$(CC) -o $(NAME) $(OBJ)

$(NAME):			all

clean:
				rm -rf $(OBJ)

fclean:				clean
				rm -rf $(NAME)

re:				fclean all
