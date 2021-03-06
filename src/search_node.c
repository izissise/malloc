/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sun Feb 16 15:24:45 2014 jonathan.collinet
*/

#include "malloc.h"

t_list		*find_free_size_node(t_list *last_node, size_t req_size)
{
  t_list	*tmp_node;

  tmp_node = last_node;
  if (last_node != NULL)
    while (tmp_node)
      {
        if (!(tmp_node->is_alloc) && (NODESIZE(tmp_node) >= req_size))
          return tmp_node;
        tmp_node = tmp_node->prev;
      }
  return (NULL);
}
