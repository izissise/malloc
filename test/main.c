/*
** main.c for main in /home/collin_b/project/malloc/PSU_2013_malloc/debug
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Mon Feb  3 11:18:40 2014 jonathan.collinet
** Last update Wed Feb  5 22:03:01 2014 jonathan.collinet
*/

#include "../src/malloc.h"

void hexdump(void *mem, unsigned int len);

void reset_malloc()
{
  void **first_addr = get_first_addr();
  *first_addr = NULL;
}

int			main()
{
  printf("ON DISPLAY LES FREE !!!\n");
  void *end;
  void* ptr = sbrk(0);

  ptr = malloc(50000);
  show_alloc_mem();
  free(ptr);
  return 0;

}
