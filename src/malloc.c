/*
** malloc.c for header in /home/collin_b/project/hello_memory
**
** Made by jonathan.collinet
** Login   <collin_b@epitech.net>
**
** Started on  Fri Jan 31 11:45:34 2014 jonathan.collinet
** Last update Sat Feb  8 18:39:53 2014 jonathan.collinet
*/

#include <pthread.h>
#include "malloc.h"

static pthread_mutex_t g_epimalloc_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
** malloc function
** in case it's the first address, we allocate a new page,
** else we try to use an already existing one
*/

void		*malloc(size_t real_size)
{
  void	*ptr;

  pthread_mutex_lock(&g_epimalloc_mutex);
  ptr = real_malloc(real_size);
  if (ptr == NULL)
    errno = ENOMEM;
  pthread_mutex_unlock(&g_epimalloc_mutex);
  return (ptr);
}

void		*realloc(void *ptr, size_t size)
{
  void	*nptr;

  pthread_mutex_lock(&g_epimalloc_mutex);
  nptr = real_realloc(ptr, size);
  if (nptr == NULL && size != 0)
    errno = ENOMEM;
  pthread_mutex_unlock(&g_epimalloc_mutex);
  return (nptr);
}

void		free(void *ptr)
{
  pthread_mutex_lock(&g_epimalloc_mutex);
  real_free(ptr);
  pthread_mutex_unlock(&g_epimalloc_mutex);
}

void		*calloc(size_t nmemb, size_t size)
{
  void	*ptr;

  pthread_mutex_lock(&g_epimalloc_mutex);
  ptr = real_calloc(nmemb, size);
  if (ptr == NULL)
    errno = ENOMEM;
  pthread_mutex_unlock(&g_epimalloc_mutex);
  return (ptr);
}
