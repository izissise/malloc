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

 // printf("%p\n", new_last_node);
  lastptr = ((t_list**)(new_last_node->next));
  *lastptr = new_last_node;
}

