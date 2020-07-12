#include "picoro/picoro.h"
#include <stdio.h>
#include <gmodule.h>

void* print_number(void* arg)
{
	int* number = (int*)arg;
	int counter = *number;
	while (counter--)
	{
		g_usleep(1000);
		yield(arg);
	}
	printf("%d\n", *number);
	return NULL;
}

int main()
{
	int counter = 0;
	int i;
	int resume_again = 1;
	int v[] = { 8, 42, 38, 111, 2, 39, 1 };
	coro coroutines[sizeof(v) / sizeof(int)];

	for (i = 0; i < sizeof(v) / sizeof(int); ++i)
		coroutines[i] = coroutine(print_number);

	while (resume_again)
	{
		resume_again = 0;
		for (i = 0; i < sizeof(v) / sizeof(int); ++i)
		{
			if (resumable(coroutines[i]))
			{
				resume(coroutines[i], &v[i]);
				resume_again = 1;
			}
		}
	}

	return 0;
}
