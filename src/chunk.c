/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Fri Feb  7 17:59:40 2014 jonathan.collinet
*/

#include "malloc.h"

int		reuse_chunk(t_list *chunk, size_t asked_size)
{
  size_t	size;

  size = NODESIZE(chunk);
  if (asked_size + sizeof(t_list) <= size)
    {
      chunk->next = (t_list*)((size_t)chunk + sizeof(t_list) + asked_size);
      init_chunk(chunk->next, chunk, size - asked_size - sizeof(t_list));
      return (1);
    }
  return (0);
}

void		update_last_size(t_list *new_last_node)
{
  t_list		**lastptr;

  lastptr = ((t_list**)(new_last_node->next));
  *lastptr = new_last_node;
}

void		set_chunk_attr(t_list *chunk, unsigned long free, size_t size)
{
  if (chunk)
    {
      chunk->is_free = free;
      chunk->size = size;
    }
}

t_list		*merge_chunk(t_list *tomerge, t_list *lastnode)
{
  tomerge->is_free = 1;
  if (tomerge->prev && tomerge->prev->is_free == 1)
    {
      tomerge->prev->next = tomerge->next;
      tomerge->next->prev = tomerge->prev;
      if (tomerge->next == lastnode->next)
        {
          update_last_size(tomerge->prev);
          lastnode = tomerge->prev;
        }
      tomerge = tomerge->prev;
    }
  if (tomerge != lastnode && tomerge->next->is_free == 1)
    {
      tomerge->next = tomerge->next->next;
      tomerge->next->prev = tomerge;
      if (tomerge->next == lastnode->next)
        update_last_size(tomerge);
    }
  return (tomerge);
}
