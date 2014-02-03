/*
** main.c for main in /home/collin_b/project/malloc/PSU_2013_malloc/debug
** 
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
** 
** Started on  Mon Feb  3 11:18:40 2014 jonathan.collinet
** Last update Mon Feb  3 18:34:39 2014 jonathan.collinet
*/

#include "../src/malloc.h"

int			main()
{
  show_alloc_mem();
  malloc(4025);
  show_alloc_mem();
  malloc(1);
  show_alloc_mem();
  return (0);
}
