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

void		init_pages(t_list *first, t_list *prev_chunk,
                   size_t size, size_t t)
{
  init_chunk(first, prev_chunk, t - sizeof(t_list));
  if (!reuse_chunk(first, first, size))
    gset_lastnode(first);
}

void		init_chunk(t_list *chunk, t_list *prev_chunk, size_t size)
{
  chunk->prev = prev_chunk;
  chunk->next = (((void*)chunk) + size + sizeof(t_list));
  chunk->is_alloc = 0;
}

void		*add_page(size_t size)
{
  void		*page_start;
  t_list	*prev_last_node;
  size_t	needed_size;

  needed_size = ALIGN(size + (sizeof(t_list) * 2), PAGESIZE);
  prev_last_node = gset_lastnode(NULL);
  page_start = sbrk(needed_size);
  if (page_start == ((void*)(-1)))
    return (NULL);
  init_pages(page_start, prev_last_node, size, needed_size);
  return (page_start);
}

