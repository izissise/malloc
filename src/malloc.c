/*
** malloc.c for header in /home/collin_b/project/hello_memory
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 11:45:34 2014 jonathan.collinet
** Last update Fri Jan 31 17:40:23 2014 jonathan.collinet
*/

#include "malloc.h"

/*
** malloc function
** in case it's the first address, we allocate a new page,
** else we try to use an already existing one
*/

void		*malloc(size_t size)
{
  static void*	first_addr = NULL;
  void*		last_addr;
  t_list*		last_node;
  t_list*		result_node;

  if (size == 0)
    return NULL;
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
        return NULL;
      reuse_chunk(result_node, size);
    }
  printf("node: %p ptr: %p next: %p\n", result_node, (void*)result_node + sizeof(t_list), result_node->next);
  result_node->is_free = 0;
  return ((void*)result_node + sizeof(t_list));
}

void		*realloc(void *ptr, size_t size)
{
  (void)ptr;
  (void)size;
  return (ptr);
}

void		free(void *ptr)
{
  (void)ptr;
}
