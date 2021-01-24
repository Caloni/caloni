#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int x1, y1, x2, y2, X2, Y2, i, j, n;
  int sz, *espiral;

  if( argc != 3 )
    return 1;

  X2 = x2 = atoi(argv[1]);
  Y2 = y2 = atoi(argv[2]);
  x1 = y1 = i = j = 0;
  n = 1;
  sz = X2 * Y2;
  espiral = calloc(sz, sizeof(int));

  while( n <= sz )
  {
    while( j < x2 )
      *(espiral + i * X2 + j++) = n++;
    x2--;
    j--;

    while( ++i < y2 )
      *(espiral + i * X2 + j) = n++;
    y2--;
    i--;

    while( --j >= x1 )
      *(espiral + i * X2 + j) = n++;
    x1++;
    j++;

    while( --i > y1 )
      *(espiral + i * X2 + j) = n++;
    y1++;
    i++;

    j++;
  }

  for( i = 0; i < Y2; ++i )
  {
    for( j = 0; j < X2; ++j )
    {
      printf("%d ", *(espiral + i * X2 + j));
    }
    printf("\n");
  }

  return 0;
}

