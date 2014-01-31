/*
** malloc.h for header in /home/collin_b/project/hello_memory
** 
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
** 
** Started on  Fri Jan 31 11:29:51 2014 jonathan.collinet
** Last update Fri Jan 31 11:52:05 2014 jonathan.collinet
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# include <unistd.h>
# include <string.h>
# include <stdio.h>

typedef struct		l_list
{
  struct l_list		*prev;
  struct l_list		*next;			// begin of area = this + struct_size
  unsigned long		is_free;
}			t_list;

/*
**	malloc.c
*/

void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			free(void *ptr);

#endif
