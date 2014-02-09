/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "malloc.h"

int		shrink_node(t_list *node, size_t size)
{
  /*if (reuse_chunk(node, size))
    {
      if (node == last_node)
        update_last_size(node->next);
      else if (node->next != lastnode)
        node->next->next->prev = node->next;
    }*/
  return (1);
}

int		realloc_special_case(t_list *node, size_t size)
{
  t_list	*last_node;
  size_t	tmpsize;

  size = ALIGN(size, CPUP2REGSIZE);
  last_node = LASTNODE(gset_break(NULL));
  if (size <= NODESIZE(node))
    return (shrink_node(node, size));
  if (node != last_node && !node->next->is_alloc
      && (tmpsize = NODESIZE(node->next) + NODESIZE(node)
                    + sizeof(t_list)) >= size)
    {
      merge_chunk(node, last_node, 1);
      last_node = LASTNODE(gset_break(NULL));
      if (reuse_chunk(node, size) && (node == last_node))
        update_last_size(node->next);
      return (1);
    }
  return (0);
}

