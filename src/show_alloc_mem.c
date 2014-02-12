/*
** show_alloc_mem.c for c in /home/collin_b/project/malloc/PSU_2013_malloc/src
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Mon Feb  3 11:03:50 2014 jonathan.collinet
** Last update Tue Feb 11 01:07:10 2014 jonathan.collinet
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
  int		i;

  i = 1;
  node = gset_lastnode(NULL);
  printf("break : %p\n", sbrk(0));
  if (node)
    {
      while ((node->prev) && (node = node->prev))
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
