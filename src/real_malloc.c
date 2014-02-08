/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sat Feb  8 18:43:19 2014 jonathan.collinet
*/

#include "malloc.h"

void		*gset_break(void *bweak)
{
  static void*	last_break = NULL;

  if (bweak)
    last_break = bweak;
  return (last_break);
}

void		*real_malloc(size_t real_size)
{
  void*		bweak;
  t_list*	last_node;
  t_list*	result_node;
  size_t	size;

  if (real_size & 0x8000000000000000)
    return (NULL);
  real_size = (real_size == 0) ? 1 : real_size;
  size = ALIGN(real_size, CPUP2REGSIZE);
  bweak = gset_break(NULL);

  if (!bweak)
    result_node = init_first_chunk(size);
  else
    {
      last_node = LASTNODE(bweak);
      if ((result_node = find_free_size_node(last_node, size)) == NULL)
        result_node = add_page(size);
      else if (reuse_chunk(result_node, size) && (result_node == last_node))
        update_last_size(last_node->next);
    }
  set_chunk_attr(result_node, 1, real_size);
  return (result_node ? ((void*)result_node + sizeof(t_list)) : NULL);
}

void		*real_realloc(void *ptr, size_t size)
{
  void		*nptr;
  t_list	*node;
  t_list	*last_node;
  size_t	tmpsize;

  if (!ptr)
    return (real_malloc(size));
  if ((size & 0x8000000000000000) || (node = CHECKVALIDNODE(ptr)) == NULL)
    return (NULL);
  if (size == 0)
    {
      real_free(ptr);
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
        node->next->next->prev = node->next;
      return (ptr);
    }
  if (node != last_node && !node->next->is_alloc
      && (tmpsize = NODESIZE(node->next) + NODESIZE(node) + sizeof(t_list)) >= size)
    {
      if (node->next == last_node)
        {
          merge_chunk(node, last_node, 1);
          memcpy(((void*)node) + sizeof(t_list), ptr, NODESIZE(node));
          return (real_malloc(size));
        }
      else
        {
          reuse_chunk(node->next, (NODESIZE(node->next) + NODESIZE(node) - size));
          merge_chunk(node, last_node, 1);
          memcpy(((void*)node) + sizeof(t_list), ptr, NODESIZE(node));
          node->is_alloc = 1;
        }
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
  void		*bweak;

  if (!ptr || !gset_break(NULL) || (cur_node = CHECKVALIDNODE(ptr)) == NULL)
    return ;
  bweak = gset_break(NULL);
  cur_node = merge_chunk(cur_node,  LASTNODE(bweak), 0);
  cur_node->is_alloc = 0;
}

void		*real_calloc(size_t nmemb, size_t size)
{
  void		*ptr;
  size_t	testsize;

  if (size == 0 || nmemb == 0)
    return (NULL);
  testsize = nmemb * size;
  if (testsize / size != nmemb)
    return (NULL);
  if ((ptr = real_malloc(nmemb * size)) != NULL)
    memset(ptr, 0, nmemb * size);
  return (ptr);
}
