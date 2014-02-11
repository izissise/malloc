/*
** main.c for main in /home/collin_b/project/malloc/PSU_2013_malloc/debug
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Mon Feb  3 11:18:40 2014 jonathan.collinet
** Last update Mon Feb 10 22:36:43 2014 jonathan.collinet
*/

#include "../src/malloc.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void    *cv(size_t size)
{
  char  *var = malloc(size);
  var[0] = 5; var[size - 1] = 10;
  return var;
}


void hexdump(void *mem, unsigned int len);

void reset_malloc()
{
  //  void **first_addr = get_first_addr();
  //  *first_addr = NULL;
}

int			main()
{
  void *ptr[11];
  void *sartbrk = sbrk(0);

malloc(3);
malloc(4096 - 48 - 8 + 1); // should be two page
  ptr[0] = malloc(5000);
  ptr[1] = malloc(200);
  show_alloc_mem();
  ptr[2] = malloc(100);
  show_alloc_mem();
  ptr[3] = malloc(300);
  ptr[4] = malloc(150);
  show_alloc_mem();
  ptr[5] = malloc(450);
  ptr[6] = malloc(100);
  ptr[7] = malloc(300);
  show_alloc_mem();
  ptr[1] = realloc(ptr[1], 250);
  show_alloc_mem();

  //  malloc(3);
  //malloc(4096 - 64 - 8); // should be one page
  //  show_alloc_mem();

  //  reset_malloc();

  //  malloc(4096 - 64 - 8 + 1); // should be two page
  show_alloc_mem();

  //  reset_malloc();
  printf("\n\non fait les vrais test ici -- \n\n");

  // TEST REALLOC

  show_alloc_mem();
  ptr[0] = malloc(5000);
  show_alloc_mem();
  ptr[1] = malloc(200);
  show_alloc_mem();
  ptr[2] = malloc(100);
  ptr[3] = malloc(300);
  ptr[4] = malloc(150);
  ptr[5] = malloc(450);
  ptr[6] = malloc(100);
  ptr[7] = malloc(300);
  show_alloc_mem();
  free(ptr[0]);
  free(ptr[2]);
  free(ptr[4]);
  free(ptr[6]);
  show_alloc_mem();
  ptr[1] = realloc(ptr[1], 250);
  show_alloc_mem();
  ptr[1] = realloc(ptr[1], 50);
  show_alloc_mem();
  ptr[1] = realloc(ptr[1], 25);
  show_alloc_mem();
  ptr[1] = realloc(ptr[1], 24);
  show_alloc_mem();
  ptr[1] = realloc(ptr[1], 34);
  show_alloc_mem();
  ptr[1] = realloc(ptr[1], 32);
  show_alloc_mem();
  ptr[1] = realloc(ptr[1], 250);
  show_alloc_mem();
  ptr[3] = realloc(ptr[3], 350);
  show_alloc_mem();
  ptr[5] = realloc(ptr[5], 1000);
  show_alloc_mem();
  ptr[7] = realloc(ptr[7], 50);
  show_alloc_mem();
  char *k;
  int j = 0;
  int rnd = open("/dev/urandom", O_RDONLY);


  //while (1)
    {
      k = malloc(4096);
      read(rnd,  k, 4096);
      printf("%d\n", j);
      k[0] = j;
      j++;
    }
  close(rnd);


  malloc(65536);
  malloc(65536);
  malloc(65536);
  malloc(65536);
  malloc(65536);
  malloc(65536);
  malloc(65536);
  malloc(65536);
  malloc(65536);
  malloc(65536);
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
      for (i = 0; i < 10; i++)
        {
          rd = rand() % 500 + 1;
          a = cv(rd);
          if (rd % 3 == 0)
            a = realloc(a, rand() % 500);
          else if (rd % 2 == 0)
            free(a);
        }
    }
  else
    {
      for (i = 0; i < 10; i++)
        {
          rd = rand() % 500 + 1;
          a = cv(rd);
          if (rd % 3 == 0)
            a = realloc(a, rand() % 500);
          else if (rd % 2 == 0)
            free(a);
        }
      exit(0);
    }
  int l;
  printf("done\n");
  waitpid(pid, &l, 0);

  //
  return 0;
}
