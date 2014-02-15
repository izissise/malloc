##
## Makefile for Makefile in /home/Epitech
##
## Made by moriss_h
## Login   <moriss_h@epitech.net>
##
## Started on  Sun Jun  9 03:35:24 2013 Hugues
## Last update Mon Feb  3 17:37:39 2014 jonathan.collinet
##

SRC		=	malloc.c \
			init_chunk.c \
			search_node.c \
			chunk.c \
			real_malloc.c \
			realloc.c \
			show_alloc_mem.c

CC		=	gcc

RM		=	rm -f

SYMLINK		=	libmy_malloc.so
NAME		=	libmy_malloc_$(HOSTTYPE).so

OBJDIR		=	obj/
SRCDIR		=	src/

CFLAGS		+=	-g -Wall -Wextra -fPIC

LDFLAGS		+=	-shared -pthread

OBJ		=	$(patsubst %.c,${OBJDIR}%.o, $(SRC))

dummy		:=	$(shell test -d $(OBJDIR) || mkdir -p $(OBJDIR))
dummy		:=	$(shell test -d $(SRCDIR) || mkdir -p $(SRCDIR))

$(OBJDIR)%.o:		$(patsubst %.c,${SRCDIR}%.c, %.c)
			@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
			@echo -e "Compiling $< { $(CFLAGS) }" | sed 's/^-e //'
			@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
		@echo -e "Linking $@ { $(LDFLAGS) }" | sed 's/^-e //'
		@$(CC) $(LDFLAGS) -o $(NAME) $(OBJ)
		@ln -f -s $(NAME) $(SYMLINK)

all:	$(NAME)

clean:
	@echo -e "Removing object !" | sed 's/^-e //'
	@$(RM) $(OBJ)

fclean:	clean
	@echo -e "Removing ${NAME} !" | sed 's/^-e //'
	@$(RM) $(NAME) $(SYMLINK)

re:	fclean all

help:
	@echo -e "Target available: all, ${NAME}, clean, fclean" | sed 's/^-e //'

.PHONY:	all clean fclean re help

