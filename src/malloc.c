/*
** malloc.c for header in /home/collin_b/project/hello_memory
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 11:45:34 2014 jonathan.collinet
** Last update Fri Feb  7 17:51:38 2014 jonathan.collinet
*/

#include "malloc.h"

/*
** malloc function
** in case it's the first address, we allocate a new page,
** else we try to use an already existing one
*/

void		*malloc(size_t real_size)
{
  void	*ptr;

  ptr = real_malloc(real_size);
  if (ptr == NULL)
    errno = ENOMEM;
  return (ptr);
}

void		*realloc(void *ptr, size_t size)
{
  void	*nptr;

  nptr = real_realloc(ptr, size);
  if (nptr == NULL)
    errno = ENOMEM;
  return (nptr);
}

void		free(void *ptr)
{
  real_free(ptr);
}

void		*calloc(size_t nmemb, size_t size)
{
  void	*ptr;

  ptr = real_calloc(nmemb, size);
  if (ptr == NULL)
    errno = ENOMEM;
  return (ptr);
}
