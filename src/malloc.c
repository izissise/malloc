/*
** malloc.c for header in /home/collin_b/project/hello_memory
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 11:45:34 2014 jonathan.collinet
** Last update Fri Jan 31 17:40:23 2014 jonathan.collinet
*/

#include "malloc.h"

void		*malloc(size_t size)
{
  static void*	first_addr = NULL;

  if (!first_addr)
    {
      first_addr = sbrk(ALIGN_PS(size + sizeof(t_list) + sizeof(intptr_t), getpagesize()));
      init_pages(first_addr, size);
      init_chunk(first_addr, NULL, ALIGN(size, 12));
      return (first_addr + sizeof(t_list));
    }
  return ((void*)0x0);
}

void		*realloc(void *ptr, size_t size)
{
  (void)ptr;
  (void)size;
  return (ptr);
}

void		free(void *ptr)
{
  (void)ptr;
}
