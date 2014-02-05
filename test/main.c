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
  void *end;
  void* ptr = sbrk(0);

  malloc(4096 - 64 - 8); // should be one page
  show_alloc_mem();

  reset_malloc();

  malloc(4096 - 64 - 8 + 1); // should be two page
  show_alloc_mem();

  reset_malloc();

  malloc(4096 - 64 - 8); // should be two page
  malloc(1); // should be two page
  show_alloc_mem();

  reset_malloc();

  void* kqj = malloc(4096 * 2 - 64 - 8); // should be 3 page
  free(kqj);
  malloc(4096 * 2 - 64 - 8); // should be 3 page
  malloc(1); // should be two page
  show_alloc_mem();

  reset_malloc();

  void* ptra = malloc(5000);
  void* ptrb = malloc(3600);
  void* ptrc = malloc(200);

	show_alloc_mem();
  free(ptra);
  free(ptrb);
  free(ptrc);
  show_alloc_mem();

/*
  malloc(500000); // should be 3 page
  malloc(4500); // should be 3 page
  malloc(4500); // should be 3 page
  malloc(4500); // should be 3 page
  malloc(1); // should be two page
  show_alloc_mem();

  reset_malloc();

  void* ptr3;
  printf("yolo\n");

  ptr3 = malloc(50);
  ptr3 = malloc(50);
  ptr3 = malloc(50);
  ptr3 = malloc(50);
  ptr3 = malloc(50);
  ptr3 = malloc(50);
  ptr3 = malloc(50);
  ptr3 = malloc(50);
  show_alloc_mem();
  free(ptr3);
  show_alloc_mem();*/

  return 0;

}
