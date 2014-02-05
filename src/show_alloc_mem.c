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

void		show_alloc_mem()
{
  t_list	*node;
  void		*bweak;
  int		i;

  i = 1;
  bweak = sbrk(0);
  printf("break : %p\n", bweak);
  if (get_first_addr())
    {
      node = LASTNODE(bweak);
      while (node->prev)
        {
          node = node->prev;
          ++i;
        }
      while(i)
        {
          if (!node->is_free || 0)
            printf("0x%lX - 0x%lX : %lu bytes\n", (size_t)(((void*)node) + sizeof(t_list)), (size_t)((((void*)node) + node->size) + sizeof(t_list)), NODEREALSIZE(node));
           else //real size
            printf("0x%lX - 0x%lX : %lu bytes free: %ld\n", (size_t)(((void*)node) + sizeof(t_list)), (size_t)((((void*)node) + NODESIZE(node)) + sizeof(t_list)), NODESIZE(node), NODEREALSIZE(node));
          node = node->next;
          --i;
        }
    }
  else
    printf("No memory allocated in our program.\n");
}
