/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Tue Feb 11 01:06:44 2014 jonathan.collinet
*/

#include "malloc.h"

void		*gset_lastnode(void *lastnode)
{
  static void*	last_node = NULL;

  if (lastnode)
    last_node = lastnode;
  return (last_node);
}

void		*real_malloc(size_t real_size)
{
  t_list*	last_node;
  t_list*	result_node;
  size_t	size;

  real_size = (real_size == 0) ? 1 : real_size;
  if (real_size & 0x8000000000000000)
    return (NULL);
  size = ALIGN(real_size, CPUP2REGSIZE);
  last_node = gset_lastnode(NULL);
  if (!last_node)
    result_node = add_page(size);
  else
    {
      if ((result_node = find_free_size_node(last_node, size)) == NULL)
        result_node = add_page(size);
      else
        reuse_chunk(result_node, last_node, size);
    }
  set_chunk_attr(result_node, 1, real_size);
  return (result_node ? ((void*)result_node + sizeof(t_list)) : NULL);
}

void		*real_realloc(void *ptr, size_t size)
{
  void		*nptr;
  t_list	*node;

  if (!ptr)
    return (real_malloc(size));
  if ((size & 0x8000000000000000) || (node = CHECKVALIDNODE(ptr)) == NULL)
    return (NULL);
  if (size == 0)
    {
      real_free(ptr);
      return (NULL);
    }
  if (realloc_special_case(node, size))
    {
      set_chunk_attr(node, 1, size);
      return (ptr);
    }
  if ((nptr = real_malloc(size)) == NULL)
    return (NULL);
  memcpy(nptr, ptr, NODESIZE(node));
  real_free(ptr);
  return (nptr);
}

void		real_free(void *ptr)
{
  t_list	*cur_node;
  void		*last_node;
  int		nbp;

  if (!ptr || !gset_lastnode(NULL) || (cur_node = CHECKVALIDNODE(ptr)) == NULL)
    return ;
  last_node = gset_lastnode(NULL);
  cur_node = merge_chunk(cur_node, last_node, 0);
  cur_node->is_alloc = 0;
  if (last_node == cur_node &&
      (NODESIZE(cur_node) > (size_t)PAGESIZE))
    {
      nbp = (NODESIZE(cur_node) /  PAGESIZE);
      cur_node->next = (void*)cur_node + sizeof(t_list) +
                       (NODESIZE(cur_node) - (nbp * PAGESIZE));
      sbrk(-(nbp * PAGESIZE));
      gset_lastnode(cur_node);
    }
}

void		*real_calloc(size_t nmemb, size_t size)
{
  void		*ptr;

  if ((ptr = real_malloc(nmemb * size)) != NULL)
    memset(ptr, 0, nmemb * size);
  return (ptr);
}
