/*
** malloc.h for header in /home/collin_b/project/hello_memory
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 11:29:51 2014 jonathan.collinet
** Last update Mon Feb  3 13:31:17 2014 jonathan.collinet
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# include <unistd.h>
# include <string.h>
# include <stdio.h>

# define PAGESIZE			getpagesize()
# define CPUP2REGSIZE		3
# define ALIGN(size, power)	(((((size) - 1) >> (power)) + 1) << (power))
# define ALIGN_PS(size, ps)	(((((size) - 1) / (ps)) + 1) * (ps))

# define LASTNODE(brkaddr)	((*(t_list**)(((void*)brkaddr) - sizeof(t_list*))))
# define NODESIZE(x)		(((size_t)((x)->next)) - (((size_t)(x)) + sizeof(t_list)))

# define SETFLAG(x, y) ((x) |= (y))
# define UNSETFLAG(x, y) ((x) &= ~(y))
# define SWITCHFLAG(x, y) ((x) ^= (y))
# define GETFLAG(x, y) ((x) & (y))
# define FLAGPOS(x) (1 << (x))

typedef struct		s_list
{
  struct s_list		*prev;
  struct s_list		*next;
  unsigned long		is_free;
  size_t		size;
}			t_list;

/*
**	malloc.c
*/

void			**get_first_addr();
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			free(void *ptr);

/*
**	init_chunk.c
*/

void			init_pages(t_list *first, t_list *prev_chunk, size_t size);
void			init_chunk(t_list *chunk, t_list *prev_chunk, size_t size);
void			*init_first_chunk(size_t size);
void			*add_page(size_t size);

/*
** search_node.c
*/

t_list		*find_free_size_node(t_list *last_node, size_t req_size);

/*
** chunk.c
*/

void			reuse_chunk(t_list *chunk, size_t asked_size);
void			update_last_size(t_list *prev_last_node);

/*
** show_alloc_mem.c
*/

void		show_alloc_mem();

#endif
