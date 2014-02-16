/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sat Feb  8 18:41:24 2014 jonathan.collinet
*/

#include "malloc.h"

void		*is_valid_ptr(void *ptr)
{
  t_list	*list;
  t_list	*lastlist;

  lastlist = gset_lastnode(NULL);
  if ((size_t)ptr % CPUP2REGSIZE != 0)
    return (NULL);
  list = ((void*)(ptr) - sizeof(t_list));
  if (((size_t)list->next % CPUP2REGSIZE != 0)
      || ((size_t)list->prev % CPUP2REGSIZE != 0)
      || list->next < list->prev || list > lastlist)
    return (NULL);
  return (list);
}

int		reuse_chunk(t_list *chunk, t_list *last_node, size_t asked_size)
{
  size_t	size;

  size = NODESIZE(chunk);
  if (asked_size + sizeof(t_list) < size)
    {
      chunk->next = (t_list*)((size_t)chunk + sizeof(t_list) + asked_size);
      init_chunk(chunk->next, chunk, size - (asked_size + sizeof(t_list)));
      if (chunk == last_node)
        gset_lastnode(chunk->next);
      return (1);
    }
  return (0);
}

void		set_chunk_attr(t_list *chunk, unsigned long alloc, size_t size)
{
  if (chunk)
    {
      chunk->is_alloc = alloc;
      if (alloc)
        chunk->is_alloc = size;
    }
}

t_list		*merge_chunk(t_list *tomerge, t_list *lastnode, short rm)
{
  if (tomerge->prev && tomerge->prev->is_alloc == 0 && !rm)
    {
      tomerge->prev->next = tomerge->next;
      tomerge = tomerge->prev;
      if (tomerge->next != lastnode->next)
        tomerge->next->prev = tomerge;
      else
        lastnode = gset_lastnode(tomerge);
    }
  if (tomerge != lastnode && tomerge->next->is_alloc == 0)
    {
      tomerge->next = tomerge->next->next;
      if (tomerge->next != lastnode->next)
        tomerge->next->prev = tomerge;
      else
        gset_lastnode(tomerge);
    }
  return (tomerge);
}

