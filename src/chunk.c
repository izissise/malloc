/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Feb  3 18:43:16 2014 jonathan.collinet
*/

#include "malloc.h"

void		reuse_chunk(t_list *chunk, size_t asked_size)
{
  size_t	size;

  size = NODESIZE(chunk);
  if (asked_size + sizeof(t_list) <= size)
    {
      chunk->next = (t_list*)((size_t)chunk + sizeof(t_list) + asked_size);
      init_chunk(chunk->next, chunk, size - asked_size - sizeof(t_list));
    }
}

void		update_last_size(t_list *prev_last_node)
{
  t_list		*tmp;
  t_list		**lastptr;

  tmp = prev_last_node->next;
  lastptr = ((t_list**)(tmp->next));
  *lastptr = tmp;
}

