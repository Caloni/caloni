#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int T, t, N, n, s, S, E, c, j, I = 0;
	char A[60 * 24];
	char Y[1000 + 1];
	scanf("%d", &T);

	for (t = 1; t <= T; ++t) {
		scanf("%d", &N);
		memset(A, 0, 60 * 24);
		memset(Y, 0, 1000 + 1);

		for (n = 0; n < N; ++n) {
			scanf("%d %d", &S, &E);
			c = 1, j = 1;
			for (s = S; s < E; ++s) {
				if (c && (A[s] & 1) != 0) c = 0;
				if (j && (A[s] & 2) != 0) j = 0;
			}
			if (c || j) {
				Y[n] = c ? 'C' : 'J';
				for (s = S; s < E; ++s)
					A[s] |= (c ? 1 : 2);
			}
			else goto impossible;
		}

		printf("Case #%d: %s\n", t, Y);
		continue;

	impossible:
		printf("Case #%d: IMPOSSIBLE\n", t);
	}

	return 0;
}
