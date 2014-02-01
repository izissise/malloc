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
  intptr_t	f_space_size;
  intptr_t	total_ps;
  intptr_t	*size_var_addr;

  total_ps = ALIGN_PS(size, getpagesize());
  size_var_addr = (intptr_t*)((intptr_t)first + (total_ps - sizeof(intptr_t)));
  f_space_size = total_ps - (sizeof(intptr_t) + (sizeof(t_list) * 2) + size);
  *size_var_addr = f_space_size;
  init_chunk(first, prev_chunk, size);
  init_chunk(first->next, first, f_space_size);
}

void		init_chunk(t_list *chunk, t_list *prev_chunk, intptr_t size)
{
  chunk->prev = prev_chunk;
  chunk->next = ((void*)chunk + size + sizeof(t_list));
  chunk->is_free = 1;
}
