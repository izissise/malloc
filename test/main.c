/*
** main.c for main in /home/collin_b/project/malloc/PSU_2013_malloc/debug
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Mon Feb  3 11:18:40 2014 jonathan.collinet
** Last update Fri Feb  7 17:59:03 2014 jonathan.collinet
*/

#include "../src/malloc.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void    *cv(size_t size)
{
  char  *var = malloc(size);
  var[0] = 5; var[size - 1] = 10;
  return var;
}


void hexdump(void *mem, unsigned int len);

void reset_malloc()
{
  //void **first_addr = get_first_addr();
  //*first_addr = NULL;
}

int			main()
{
  void *end;
  void* ptr = sbrk(0);

  show_alloc_mem();


malloc(3);
  //malloc(4096 - 64 - 8); // should be one page
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

  reset_malloc();

  printf("\n\non fait les vrais test ici -- \n\n");

  ptra = malloc(500);
  ptrb = malloc(200);
  ptrc = malloc(300);
  show_alloc_mem();
  ptra = realloc(ptra, 250);
  show_alloc_mem();
  ptra = realloc(ptrb, 650);
  show_alloc_mem();
  ptra = realloc(ptrc, 150);
  show_alloc_mem();
  ptra = realloc(ptra, 250);
  show_alloc_mem();
  ptra = realloc(ptrb, 350);
  show_alloc_mem();
  free(ptra);
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

  printf("vfork test\n");



//  a = malloc(4024);


  pid_t pid = vfork();
  char *a;
  int   i;
  int   rd;

  if (pid)
    { //daddy
      for (i = 0; i < 1000; i++)
        {
          rd = rand() % 500 + 1;
          a = cv(rd);
          if (rd % 3 == 0)
            a = realloc(a, rd * 2);
          else if (rd % 2 == 0)
            free(a);
        }
    }
  else
    {
      for (i = 0; i < 1000; i++)
        {
          rd = rand() % 500 + 1;
          a = cv(rd);
          if (rd % 3 == 0)
            a = realloc(a, rd * 2);
          else if (rd % 2 == 0)
            free(a);
        }
      exit(0);
    }
  int l;
  printf("done\n");
  waitpid(pid, &l, 0);

  return 0;

}
