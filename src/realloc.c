/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Feb 10 21:59:45 2014 jonathan.collinet
*/

#include "malloc.h"

int		shrink_node(t_list *node, t_list *last_node, size_t size)
{
  if (reuse_chunk(node, last_node, size))
    {
      node = node->next;
      last_node = gset_lastnode(NULL);
      if (node != last_node)
        merge_chunk(node, last_node, 1);
    }
  return (1);
}

int		realloc_special_case(t_list *node, size_t size)
{
  t_list	*last_node;

  size = ALIGN(size, CPUP2REGSIZE);
  last_node = gset_lastnode(NULL);
  if (size <= NODESIZE(node))
    return (shrink_node(node, last_node, size));
  if (node != last_node && !node->next->is_alloc
      && (NODESIZE(node->next) + NODESIZE(node) + sizeof(t_list)) > size)
    {
      if (last_node->next == node->next)
        {
          merge_chunk(node, last_node, 1);
          return (1);
        }
    }
  return (0);
}
