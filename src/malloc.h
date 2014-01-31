/*
** malloc.h for header in /home/collin_b/project/hello_memory
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 11:29:51 2014 jonathan.collinet
** Last update Fri Jan 31 17:13:35 2014 jonathan.collinet
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# include <unistd.h>

# define ALIGN(size, power)	(((((size) - 1) >> (power)) + 1) << (power))
# define ALIGN_PS(size, ps)	(((((size) - 1) / (ps)) + 1) * (ps))

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

/*
**	init_chunk.c
*/

void			init_pages(t_list *first, intptr_t size);
void			init_chunk(t_list *chunk, t_list *prev_chunk, intptr_t size);

/*
**	linked_list.c
*/

int			add_chunk(t_list *new_chunk, size_t size_chunk);

#endif
