#include <ctype.h>
#include <stdio.h>

int main() {
	int T, t;
	char S[105];
	char S1[100 * 10 * 2];
	char* pS, * pS1, diff, digit, last_digit;
	scanf("%d", &T);

	for (t = 1; t <= T; ++t) {
		scanf("%s", S);
		pS = S, pS1 = S1;
		last_digit = '0';
		while (isdigit(digit=*pS++)) {
			diff = digit - last_digit;
			if( diff>0 )
				while( diff-->0 )
					*pS1++ = '(';
			else if( diff<0 )
				while( diff++<0 )
					*pS1++ = ')';
			last_digit = digit;
			*pS1++ = last_digit;
		}
		while( isdigit(--last_digit) )
					*pS1++ = ')';
		*pS1 = 0;
		printf("Case #%d: %s\n", t, S1);
	}

	return 0;
}
