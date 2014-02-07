#include <stdlib.h>

void    *cv(size_t size)
{
  char  *var = malloc(size);
  var[0] = 5; var[size - 1] = 10;
  return var;
}

int main()
{
  char *a;
  int   i;
  int   rd;

  for (i=0; i < 1000000; i++)
    {
      rd = rand() % 500 + 1;
      a = cv(rd);
      if (rd % 3 == 0)
        a = realloc(a, rd * 2);
      else if (rd % 2 == 0)
        free(a);
    }
//  a = malloc(4024);
  return 0;
}
