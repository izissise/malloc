/*
** malloc.c for header in /home/collin_b/project/hello_memory
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 11:45:34 2014 jonathan.collinet
** Last update Fri Feb  7 17:51:38 2014 jonathan.collinet
*/

#include "malloc.h"

void		*gset_break(void *bweak)
{
  static void*	last_break = NULL;

  if (bweak)
    last_break = bweak;
  return (last_break);
}

/*
** malloc function
** in case it's the first address, we allocate a new page,
** else we try to use an already existing one
*/

void		*malloc(size_t real_size)
{
  void*		bweak;
  t_list*	last_node;
  t_list*	result_node;
  size_t	size;

  if (real_size == 0 || (real_size & 0x8000000000000000))
    {
      errno = ENOMEM;
      return (NULL);
    }
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
  if (result_node)
    {
      result_node->is_free = 0;
      result_node->size = real_size;
    }
  else
    errno = ENOMEM;
  //return (result_node ? ((void*)result_node + sizeof(t_list)) : NULL);
  return (((void*)result_node + sizeof(t_list)));
}

void		*realloc(void *ptr, size_t size)
{
  void		*nptr;
  t_list	*node;
  t_list	*last_node;
  size_t	tmpsize;

  if (!ptr)
    return (malloc(size));
  if ((size & 0x8000000000000000) || (node = CHECKVALIDNODE(ptr)) == NULL)
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
	node->next->next->prev = node->next;
      //      else
      //merge_chunk(node->next, node->next->next);
      return (ptr);
    }
  if (node != last_node && node->next->is_free
      && (tmpsize = NODESIZE(node->next) + NODESIZE(node) + sizeof(t_list)) >= size)
    {
      if (node->next == last_node)
	{
	  merge_chunk(node, last_node);
	  return (malloc(size));
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

  if (!ptr || !gset_break(NULL) || (cur_node = CHECKVALIDNODE(ptr)) == NULL)
    return ;
  bweak = gset_break(NULL);
  cur_node = merge_chunk(cur_node,  LASTNODE(bweak));
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*ptr;
  size_t	testsize;

  if (size == 0 || nmemb == 0)
    return (NULL);
  testsize = nmemb * size;
  if (testsize / size != nmemb)
    return (NULL);
  if ((ptr = malloc(nmemb * size)) != NULL)
    memset(ptr, 0, nmemb * size);
  return (ptr);
}
