/*
** show_alloc_mem.c for c in /home/collin_b/project/malloc/PSU_2013_malloc/src
** 
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
** 
** Started on  Mon Feb  3 11:03:50 2014 jonathan.collinet
** Last update Mon Feb  3 22:49:00 2014 jonathan.collinet
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
	  if (!node->is_free)
	    printf("%p - %p : %lu bytes\n", node, (void*)(node + node->size), node->size);
	  node = node->next;
	  --i;
	}
    }
  else
    printf("No memory allocated in our program.\n");
}
