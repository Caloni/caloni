#include <stdio.h>
#include <string.h>

int M[100][100];
int J[100];

int main() {
	int T, N, n, t, i, j, k, ic, ii, jj, kk;
	scanf("%d", &T);

	for (t = 1; t <= T; ++t) {
		scanf("%d", &N);
		memset(J, 0, N * sizeof(int));
		ii = 0, jj = 0, kk = 0;

		for (j = 0; j < N; ++j) {
			ic = 0;

			for (i = 0; i < N; ++i) {
				scanf("%d", &n);
				M[i][j] = n;

				for (k = 0; k < i; ++k) {
					if (!ic && M[k][j] == M[i][j])
						ic = 1;
				}

				if (i == j)
					kk += M[i][j];
			}
			ii += ic;

		}

		for (i = 0; i < N; ++i) {
			for (j = 0; j < N; ++j) {
				for (k = 0; k < j; ++k) {
					if (!J[i] && M[i][k] == M[i][j]) {
						J[i] = 1;
						jj++;
					}
				}
			}
		}

		printf("Case #%d: %d %d %d\n",
			t, kk, ii, jj);
	}

	return 0;
}
