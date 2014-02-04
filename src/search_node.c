/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Feb  3 22:54:59 2014 jonathan.collinet
*/

#include "malloc.h"

t_list	*find_free_size_node(t_list *last_node, size_t req_size)
{
  t_list	*tmp_node;

  tmp_node = last_node;
  while (tmp_node)
    {
      if (tmp_node->is_free
          && (NODESIZE(tmp_node) >= req_size))
        return tmp_node;
      tmp_node = tmp_node->prev;
    }
  return (NULL);
}
