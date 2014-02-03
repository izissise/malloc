/*
** show_alloc_mem.c for c in /home/collin_b/project/malloc/PSU_2013_malloc/src
** 
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
** 
** Started on  Mon Feb  3 11:03:50 2014 jonathan.collinet
** Last update Mon Feb  3 13:12:09 2014 jonathan.collinet
*/

#include "malloc.h"

void		show_alloc_mem()
{
  t_list	*node;
  void		*bweak;

  bweak = sbrk(0);
  printf("break : %p\n", bweak);
  if ((node = get_first_addr()))
    while (node)
      {
	printf("%p - %p : %lu bytes\n", node, node->next, NODESIZE(node));
	node = node->next;
      }
  else
    printf("No memory allocated in our program.\n");
}
