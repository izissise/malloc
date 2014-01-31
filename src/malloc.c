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

  if (!first_addr)
    {
      first_addr = sbrk(ALIGN_PS(size + sizeof(t_list) + sizeof(intptr_t), getpagesize()));
      if (first_addr == ((void*)(-1)))
        return NULL;
      init_pages(first_addr, NULL, size);
      result_node = first_addr;
      result_node->is_free = 0;
    }
  else
    {
      last_addr = sbrk(0);
      last_node = LASTNODE(last_addr);
      result_node = find_free_size_node(last_node, size);
      if (result_node == last_node)
        return NULL;

    }
  return (result_node + sizeof(t_list));
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
