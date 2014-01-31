/*
** linked_list.c for cest kwa le pointeur nest ?? in /home/collin_b/project/hello_memory
** 
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
** 
** Started on  Fri Jan 31 11:52:32 2014 jonathan.collinet
** Last update Fri Jan 31 17:13:18 2014 jonathan.collinet
*/

#include "malloc.h"

int		add_chunk(t_list *new_chunk, size_t size_chunk)
{
  if (!size_chunk)
    return (0);
  if (new_chunk)
    init_list(&(tmp), NULL);
  else if (!tmp->back)
    {
      init_list(&(tmp->next), tmp);
    }
}
