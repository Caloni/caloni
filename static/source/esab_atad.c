#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Windows.h>

unsigned mask(unsigned B) {
	unsigned m = 0, i;
	for (i = 0; i < B; ++i)
		m |= 1 << i;
	return m;
}

unsigned reverse(unsigned n, unsigned B) {
	unsigned i, t, r = 0;
	for(i=0; i < B; ++i ) {
		t = (n & (1 << i));
		if( t )
			r |= (1 << ((B - 1) - i));
	}
	return r;
}

int main() {
	unsigned T, t, B, i, j, b, n, n2;
	char v;

	//while (!IsDebuggerPresent())
		//Sleep(1000);
	scanf("%d %d", &T, &B);

	for (t = 1; t <= T; ++t) {
		n = n2 = j = 0;

		while (j < B / 2 - 1) {
			for (i = j; i < j + 5; ++i) {
				printf("%d\n", i + 1); fflush(stdout);
				scanf("%d", &b);
				n |= (b << i);
			}
			for (i = B - 1; i > B - 6; --i) {
				printf("%d\n", i + 1); fflush(stdout);
				scanf("%d", &b);
				n |= (b << i);
			}
			for (i = j; i < j + 5; ++i) {
				printf("%d\n", i + 1); fflush(stdout);
				scanf("%d", &b);
				n2 |= (b << i);
			}
			for (i = B - 1; i > B - 6; --i) {
				printf("%d\n", i + 1); fflush(stdout);
				scanf("%d", &b);
				n2 |= (b << i);
			}

			if (n == n2)
				;
			else if (n == (~n2 & mask(i)))
				n = ~n & mask(i);
			else if (reverse(n, B) == n2)
				n = reverse(n, B);
			else
				n = reverse(~n & mask(i), B);

			j += 5;
		}
		
		for (i = 0; i < B; ++i) {
			printf("%c", ((n >> i) & 1) ? '1' : '0'); fflush(stdout);
		}
		printf("\n"); fflush(stdout);
		do scanf("%c", &v);
		while (v != 'Y' && v != 'N');
		if (v != 'Y')
			return t;
	}

	return 0;
}
