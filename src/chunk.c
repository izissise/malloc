/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Thu Feb  6 14:21:06 2014 jonathan.collinet
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

void		update_last_size(t_list *new_last_node)
{
  t_list		**lastptr;

  printf("new_last_node : %p -- new_last_node->next : %p\n", new_last_node, new_last_node->next);
  lastptr = ((t_list**)(new_last_node->next));
  *lastptr = new_last_node;
}
