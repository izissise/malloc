/*
** malloc.c for header in /home/collin_b/project/hello_memory
** 
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
** 
** Started on  Fri Jan 31 11:45:34 2014 jonathan.collinet
** Last update Fri Jan 31 12:00:02 2014 jonathan.collinet
*/

#include "malloc.h"

void		*malloc(size_t size)
{
  if (!size)
    printf("yollolollol!\n");
  return ((void*)0x0);
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
