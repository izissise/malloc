/*
** show_alloc_mem.c for c in /home/collin_b/project/malloc/PSU_2013_malloc/src
** 
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
** 
** Started on  Mon Feb  3 11:03:50 2014 jonathan.collinet
** Last update Mon Feb  3 12:02:48 2014 jonathan.collinet
*/

#include "malloc.h"

void		show_alloc_mem()
{
  t_list	*last_node;
  void		*brek;

  brek = sbrk(0);
  printf("break : %p\n", brek);
  if (get_first_addr())
    {
      last_node = LASTNODE(brek);
      printf("%p\n", last_node);
      while (last_node)
	{
	  printf("%p - %p : %u bytes\n", last_node, LASTNODE(last_node), (unsigned int)(last_node - LASTNODE(last_node)));
	  last_node = last_node->prev;
	}
    }
  else
    printf("No memory allocated in our program.\n");
}
