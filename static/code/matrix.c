/** This is a bidimensional matrix student sample.

@author Wanderley Caloni <wanderley.caloni@gmail.com>
@date 2020-06
*/

#include <stdio.h>

int matrix()
{
  int matrix[3][3];
    int i, j, number;

    number = 1;
    for( i = 0; i < 3; ++i )
    {
        for( j = 0; j < 3; ++j )
        {
            matrix[i][j] = number;
            number = number + 1;
        }
    }

    for( i = 0; i < 3; ++i )
    {
        for( j = 0; j < 3; ++j )
        {
          printf(" %d", matrix[i][j]);
        }
        printf("\n");
    }
		printf("\n");
}

