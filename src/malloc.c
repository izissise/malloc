/*
** malloc.c for header in /home/collin_b/project/hello_memory
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 11:45:34 2014 jonathan.collinet
** Last update Mon Feb  3 22:52:47 2014 jonathan.collinet
*/

#include "malloc.h"

/*
** malloc function
** in case it's the first address, we allocate a new page,
** else we try to use an already existing one
*/

static void*	first_addr = NULL;

void		*get_first_addr()
{
  return (first_addr);
}

void		*malloc(size_t size)
{
  void*		last_addr;
  t_list*	last_node;
  t_list*	result_node;
  size_t	real_size;

  if (size == 0)
    return (NULL);
  real_size = size;
  size = ALIGN(size, CPUP2REGSIZE);
  if (!first_addr)
    {
      first_addr = init_first_chunk(size);
      result_node = first_addr;
    }
  else
    {
      last_addr = sbrk(0);
      last_node = LASTNODE(last_addr);
      if ((result_node = find_free_size_node(last_node, size)) == NULL)
        result_node = add_page(size);
      else
        {
          reuse_chunk(result_node, size);
          if (result_node == last_node)
            update_last_size(last_node);
        }
    }
  result_node->is_free = 0;
  result_node->size = real_size;
  printf("Last node is %p\n", LASTNODE(sbrk(0)));
  return ((void*)result_node + sizeof(t_list));
}

void		*realloc(void *ptr, size_t size)
{
  void	*nptr;

  nptr = malloc(size);
  memcpy(nptr, ptr, size);
  return (nptr);
}

void		free(void *ptr)
{
  (void)ptr;
}
