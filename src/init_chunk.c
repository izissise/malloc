/*
** init_chunk.c for init_chunk in /home/collin_b/project/hello_memory/src
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 17:13:01 2014 jonathan.collinet
** Last update Mon Feb  3 22:54:39 2014 jonathan.collinet
*/

#include "malloc.h"

void		init_pages(t_list *first, t_list *prev_chunk, size_t size)
{
  size_t	f_space_size;
  size_t	total_ps;
  intptr_t	*size_var_addr;

  total_ps = ALIGN_PS((size + sizeof(intptr_t) + sizeof(t_list) * 2), sysconf(_SC_PAGESIZE));
  size_var_addr = (intptr_t*)((intptr_t)first + (total_ps - sizeof(intptr_t)));
  f_space_size = total_ps - (sizeof(intptr_t) + (sizeof(t_list) * 2) + size);
  *size_var_addr = f_space_size;
  init_chunk(first, prev_chunk, size);
  init_chunk(first->next, first, f_space_size);
}

void		init_chunk(t_list *chunk, t_list *prev_chunk, size_t size)
{
  chunk->prev = prev_chunk;
  chunk->next = ((void*)chunk + size + sizeof(t_list));
  chunk->is_free = 1;
  chunk->size = size;
}

void		*init_first_chunk(size_t size)
{
  t_list	*first_addr;

  first_addr = sbrk(ALIGN_PS(size + (sizeof(t_list) * 2) + sizeof(intptr_t), sysconf(_SC_PAGESIZE)));
  if (first_addr == ((void*)(-1)))
    return (NULL);
  init_pages(first_addr, NULL, size);
  return (first_addr);
}

void		*add_page(size_t size)
{
  void		*page_start;
  t_list	*prev_last_node;

  page_start = sbrk(ALIGN_PS(size + (sizeof(t_list) * 2) + sizeof(intptr_t), sysconf(_SC_PAGESIZE)));
  prev_last_node = LASTNODE(page_start);
  prev_last_node->next = ((void*)prev_last_node->next) + sizeof(intptr_t);
  init_pages(page_start, prev_last_node, size);
  return (page_start);
}
