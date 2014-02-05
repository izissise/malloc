/*
** main.c for main in /home/collin_b/project/malloc/PSU_2013_malloc/debug
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Mon Feb  3 11:18:40 2014 jonathan.collinet
** Last update Wed Feb  5 14:13:19 2014 jonathan.collinet
*/

#include "../src/malloc.h"

void hexdump(void *mem, unsigned int len);

int			main()
{
  malloc(50);
  show_alloc_mem();
  malloc(50);
  show_alloc_mem();
  malloc(50);
  show_alloc_mem();
  malloc(50);
  show_alloc_mem();
  malloc(5000);
  show_alloc_mem();
  malloc(50);
  show_alloc_mem();
  malloc(50);
  show_alloc_mem();
  return 0;
}
