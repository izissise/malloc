/*
** malloc.h for header in /home/collin_b/project/hello_memory
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 11:29:51 2014 jonathan.collinet
** Last update Sun Feb 16 15:29:38 2014 jonathan.collinet
*/

#ifndef MALLOC_H_
# define MALLOC_H_

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

# ifdef __i386__
#  define CPUP2REGSIZE		4
# else
#  define CPUP2REGSIZE		8
# endif

# define PAGESIZE	getpagesize()
# define ALIGN(s, p)	(((size_t)(s) + ((p) - 1)) & ~(size_t)((p) - 1))

# define NODESIZE(x) (((size_t)((x)->next)) - (((size_t)(x)) + sizeof(t_list)))
# define NODEREALSIZE(x)	((x)->is_alloc)
# define CHECKVALIDNODE(x)	(is_valid_ptr(x))

typedef struct		s_list
{
  struct s_list		*prev;
  struct s_list		*next;
  unsigned long		is_alloc;
}			t_list;

/*
**	malloc.c
*/

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);
void	*calloc(size_t nmemb, size_t size);

/*
**	real_malloc.c
*/

void	*gset_lastnode(void *lastnode);
void	*real_malloc(size_t real_size);
void	*real_realloc(void *ptr, size_t size);
void	real_free(void *ptr);
void	*real_calloc(size_t nmemb, size_t size);

/*
**	realloc.c
*/

int	shrink_node(t_list *node, t_list *last_node, size_t size);
int	realloc_special_case(t_list *node, size_t size);

/*
**	init_chunk.c
*/

void	init_pages(t_list *first, t_list *prev_chunk,
                   size_t size, size_t t);
void	init_chunk(t_list *chunk, t_list *prev_chunk, size_t size);
void	*add_page(size_t size);

/*
**	search_node.c
*/

t_list	*find_free_size_node(t_list *last_node, size_t req_size);

/*
**	chunk.c
*/

void	*is_valid_ptr(void *ptr);
int	reuse_chunk(t_list *chunk, t_list *last_node, size_t asked_size);
t_list	*merge_chunk(t_list *tomerge, t_list *lastnode, short rm);
void	set_chunk_attr(t_list *chunk, unsigned long alloc, size_t size);

/*
**	show_alloc_mem.c
*/

void	print_node(t_list *node);
void	show_alloc_mem();

#endif
