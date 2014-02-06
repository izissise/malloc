/*
** malloc.c for header in /home/collin_b/project/hello_memory
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 11:45:34 2014 jonathan.collinet
** Last update Thu Feb  6 11:27:19 2014 jonathan.collinet
*/

#include "malloc.h"

/*
** malloc function
** in case it's the first address, we allocate a new page,
** else we try to use an already existing one
*/

static void*	first_addr = NULL;

void		**get_first_addr()
{
  return (&first_addr);
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
  return ((void*)result_node + sizeof(t_list));
}

void		*realloc(void *ptr, size_t size)
{
  void		*nptr;
  t_list	*node;
  size_t	tmpsize;

  if (!ptr)
    return (malloc(size));
  if ((node = CHECKVALIDNODE(ptr)) == NULL)
    return (NULL);
  if (size == 0)
    {
      free(ptr);
      return (NULL);
    }
  size = ALIGN(size, CPUP2REGSIZE);
  if (size <= NODESIZE(node)) //if lots of free space add a node ?
    return (ptr);
  if (node != LASTNODE(sbrk(0)) && node->next->is_free
      && (tmpsize = NODESIZE(node->next) + NODESIZE(node) + sizeof(t_list)) >= size)
    {
      if (tmpsize - sizeof(t_list) - ALIGN(1, CPUP2REGSIZE) >= size)
        {
          node->next = ((void*)node + size + sizeof(t_list));
          init_chunk(node->next, node, tmpsize - sizeof(t_list) - size);
        }
      else
        {
          node->next = node->next->next;
          node->next->prev = node;
        }
      return (ptr);
    }
  if ((nptr = malloc(size)) == NULL)
    return (NULL);
  memcpy(nptr, ptr, NODESIZE(node));
  free(ptr);
  return (nptr);
}

void		free(void *ptr)
{
  t_list	*cur_node;
  t_list	*last_node;
  void		*bweak;

  if (!ptr || (cur_node = CHECKVALIDNODE(ptr)) == NULL)
    return ;
  bweak = sbrk(0);
  last_node = LASTNODE(bweak);
  cur_node->is_free = 1;
  if (cur_node->prev && cur_node->prev->is_free == 1)
    {
      cur_node->prev->next = cur_node->next;
      cur_node->next->prev = cur_node->prev;
      cur_node = cur_node->prev;
    }
  if (cur_node != last_node && cur_node->next->is_free == 1)
    {
      cur_node->next = cur_node->next->next;
      cur_node->next->prev = cur_node;
    }
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*ptr;

  if ((ptr = malloc(nmemb * size)) != NULL)
    memset(ptr, 0, nmemb * size);
  return (ptr);
}

