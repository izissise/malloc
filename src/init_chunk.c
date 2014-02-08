/*
** init_chunk.c for init_chunk in /home/collin_b/project/hello_memory/src
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 17:13:01 2014 jonathan.collinet
** Last update Thu Feb  6 11:01:05 2014 jonathan.collinet
*/

#include "malloc.h"

void		*my_sbrk(intptr_t size)
{
  int	ret;
  void	*lastbweak;

  lastbweak = gset_break(NULL);
  if (lastbweak == NULL)
    lastbweak = sbrk(0);
  ret = brk(lastbweak + size);
  if (ret == -1)
    return ((void*)((size_t)ret));
  gset_break(lastbweak + size);
  return (lastbweak);
}

void		init_pages(t_list *first, t_list *prev_chunk, size_t size)
{
  size_t		total_ps;
  size_t		f_space_size;
  t_list		**last_list;

  total_ps = ALIGN_PS((size + sizeof(t_list*) + sizeof(t_list) * 2), PAGESIZE);
  last_list = (t_list**)((void*)first + (total_ps - sizeof(t_list*)));
  f_space_size = total_ps - (sizeof(t_list*) + (sizeof(t_list) * 2) + size);
  init_chunk(first, prev_chunk, size);
  init_chunk(first->next, first, f_space_size);
  *last_list = first->next;
}

void		init_chunk(t_list *chunk, t_list *prev_chunk, size_t size)
{
  chunk->prev = prev_chunk;
  chunk->next = ((void*)chunk + size + sizeof(t_list));
  chunk->is_alloc = 0;
}

void		*init_first_chunk(size_t size)
{
  t_list	*first_addr;
  size_t	needed_size;

  needed_size = ALIGN_PS(size + (sizeof(t_list) * 2) + sizeof(t_list*),
                         PAGESIZE);
  first_addr = my_sbrk(needed_size);
  if (first_addr == ((void*)(-1)))
    return (NULL);
  init_pages(first_addr, NULL, size);
  return (first_addr);
}

void		*add_page(size_t size)
{
  void		*page_start;
  t_list	*prev_last_node;

  page_start = my_sbrk(ALIGN_PS(size + (sizeof(t_list) * 2) + sizeof(t_list*),
                                PAGESIZE));
  if (page_start == ((void*)(-1)))
    return (NULL);
  prev_last_node = LASTNODE(page_start);
  prev_last_node->next = ((void*)prev_last_node->next) + sizeof(t_list*);
  init_pages(page_start, prev_last_node, size);
  return (page_start);
}

