/*
** malloc.c for header in /home/collin_b/project/hello_memory
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 11:45:34 2014 jonathan.collinet
** Last update Thu Feb  6 21:15:16 2014 jonathan.collinet
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
      else if (reuse_chunk(result_node, size) && (result_node == last_node))
        update_last_size(last_node->next);
    }
  if (result_node)
    {
      result_node->is_free = 0;
      result_node->size = real_size;
    }
  return ((void*)result_node + sizeof(t_list));
}

void		*realloc(void *ptr, size_t size)
{
  void		*nptr;
  t_list	*node;
  t_list	*last_node;
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
  last_node = LASTNODE(sbrk(0));
  if (size <= NODESIZE(node)) //if lots of free space add a node ?
    {
      reuse_chunk(node, size);
      if (node->next == last_node)
        update_last_size(node->next);
      else
        {
          init_chunk(node->next->next, node->next, (node->next->next + sizeof(t_list)) - node->next);
          merge_chunk(node->next, last_node);
        }
      return (ptr);
    }
  if (node != last_node && node->next->is_free
      && (tmpsize = NODESIZE(node->next) + NODESIZE(node) + sizeof(t_list)) >= size)
    {
      if (node->next == last_node)
        update_last_size(node->next);
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
  void		*bweak;

  if (!ptr || !first_addr || (cur_node = CHECKVALIDNODE(ptr)) == NULL)
    return ;
  bweak = sbrk(0);
  cur_node = merge_chunk(cur_node,  LASTNODE(bweak));
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*ptr;
  size_t		testsize;

  if (size == 0 || nmemb == 0)
    return (NULL);
  testsize = nmemb * size;
  if (testsize / size != nmemb)
    return (NULL);
  if ((ptr = malloc(nmemb * size)) != NULL)
    memset(ptr, 0, nmemb * size);
  return (ptr);
}

