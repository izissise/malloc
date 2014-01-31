/*
** malloc.c for header in /home/collin_b/project/hello_memory
** 
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
** 
** Started on  Fri Jan 31 11:45:34 2014 jonathan.collinet
** Last update Fri Jan 31 17:11:55 2014 jonathan.collinet
*/

#include "malloc.h"

void		*malloc(size_t size)
{
  static void*	first_addr = NULL;

  if (!first_addr)
    {
      init_page(size);
      first_addr = sbrk(align(size + sizeof(t_list) + sizeof(intptr_t), 12));
      init_chunk(first_addr, NULL, align(size, 12));
      add_chunk();
      return (first_addr + sizeof(t_list));
    }
  
}

void		*realloc(void *ptr, size_t size)
{
  if (!ptr && !size)
    printf("yolo!\n");
  return (ptr);
}

void		free(void *ptr)
{
  if (!ptr)
    return ;
}
