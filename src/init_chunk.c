/*
** init_chunk.c for init_chunk in /home/collin_b/project/hello_memory/src
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 17:13:01 2014 jonathan.collinet
** Last update Fri Jan 31 17:43:02 2014 jonathan.collinet
*/

#include "malloc.h"

void		init_pages(t_list *first, t_list *prev_chunk, intptr_t size)
{
  t_list	*second;
  intptr_t	*s;
  intptr_t	total_ps;

  second = NULL;
  total_ps = ALIGN_PS(size, getpagesize());
  s = ((intptr_t*)total_ps - sizeof(intptr_t));
  *s = total_ps - (sizeof(intptr_t) - (sizeof(t_list) * 2) - size);
  init_chunk(second, first, *s);
  init_chunk(first, prev_chunk, size);
}

void		init_chunk(t_list *chunk, t_list *prev_chunk, intptr_t size)
{
  chunk->prev = prev_chunk;
  chunk->next = ((t_list*)size + sizeof(t_list));
  chunk->is_free = 1;
}
