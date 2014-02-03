/*
** main.c for main in /home/collin_b/project/malloc/PSU_2013_malloc/debug
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Mon Feb  3 11:18:40 2014 jonathan.collinet
** Last update Mon Feb  3 21:08:56 2014 jonathan.collinet
*/

#include "../src/malloc.h"

void hexdump(void *mem, unsigned int len);

int			main()
{
void* ptr = sbrk(0);
  show_alloc_mem();
  malloc(4025);
  show_alloc_mem();
  malloc(1);
  show_alloc_mem();
  void *end = sbrk(0);
  hexdump(ptr, end - ptr);
  return 0;
}
