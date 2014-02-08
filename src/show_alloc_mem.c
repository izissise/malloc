/*
** show_alloc_mem.c for c in /home/collin_b/project/malloc/PSU_2013_malloc/src
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Mon Feb  3 11:03:50 2014 jonathan.collinet
** Last update Wed Feb  5 16:55:40 2014 jonathan.collinet
*/

#include "malloc.h"

void		print_node(t_list *node)
{
  printf("0x%lX - 0x%lX : %lu bytes\n",
         ((size_t)node) + sizeof(t_list),
         (((size_t)node) + NODEREALSIZE(node)) + sizeof(t_list),
         NODEREALSIZE(node));
}

void		show_alloc_mem()
{
  t_list	*node;
  void		*bweak;
  int		i;

  i = 1;
  bweak = gset_break(NULL);
  printf("break : %p\n", sbrk(0));
  if (bweak)
    {
      node = LASTNODE(bweak);
      while ((node = node->prev) && (node->prev))
        ++i;
      while (i)
        {
          if (node->is_alloc)
            print_node(node);
          node = node->next;
          --i;
        }
    }
  else
    printf("No memory allocated in our program.\n");
}
