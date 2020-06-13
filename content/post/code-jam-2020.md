---
categories: [ "code" ]
date: "2020-04-05"
tags: [ "draft", "puzzle" ]
title: "Code Jam 2020"
---
O Code Jam esse ano terminou rápido para mim. Estou enferrujado? Nem tanto. Apenas dei menos atenção ao evento no seu início, mas apesar de me concentrar nas últimas 11 horas não tive um resultado satisfatório, obtendo 24 pontos ao total, o que não me dá direito para o torneio, que exige pelo menos 30.

Minha abordagem nesse problema foi o básico de ir lendo os valores e verificando para cada novo elemento da linha se havia repetição nos valores já lidos da mesma linha. Eu me compliquei na hora de fazer a mesma coisa para as colunas, pois inseri essa checagem dentro do loop da linha, evitando, assim, sempre a última coluna. Foi a parte que mais perdi tempo útil de todo o torneio (não li todos os exercícios antes).

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

Esse foi o mais simples de todos. Entendendo o enunciado, em que o título dá uma dica valiosa sobre o comportamento do algoritmo (aninhado), foi só usar a mesma lógica que nós programadores usamos na hora de aninhar parênteses.

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

Esse exercício me parecia fácil no começo. Desenhei na minha janela um esboço da ideia inicial, que era manter um registro de todos os minutos de um dia e a cada nova tarefa popular cada minuto. Meu erro principal foi não considerar que todos os minutos de uma tarefa devem estar sob a responsabilidade de apenas uma pessoa. Corrigido isso, meu código passou nos poucos testes disponíveis no problema, mas não passou na hora de submeter. Estou sem saber até agora o que fiz de errado.

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

Esse foi o mais divertido porque envolveu mexer em ambiente. O script iterativo do Google (interactiverunner.py) não funcionou direito no Windows, mas depois de uns testes no WSL percebi que o erro mesmo é não dar flush nos printf do meu lado. Sempre haverá problemas de buffer em stdin/stdout.

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
    	unsigned T, t, B, i, j, b, n0, n, n2;
    	char v;
    
    	while (!IsDebuggerPresent())
    		Sleep(1000);
    	scanf("%d %d", &T, &B);
    
    	for (t = 1; t <= T; ++t) {
    		n0 = n = n2 = j = 0;
    
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
    			else if (n == (~n2 & mask(B)))
    				n = ~n & mask(B);
    			else if (reverse(n, B) == n2)
    				n = reverse(n, B);
    			else
    				n = reverse(~n & mask(B), B);
    
    			if( j > 0 )
    				n &= (mask(10) << 5);
    			else
    				n &= ~(mask(10) << 5);
    			n0 |= n;
    			n = n2 = 0;
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

De qualquer forma, não consegui resolver mais do que 10 bits. Já estava ficando tarde e eu me perdi em digressões de como tornar o código maleável para adivinhar mais que duas viradas quânticas. Deixei esse código experimental de lado e fui ler o próximo.

Apenas li o enunciado. Ele falava sobre o quadrado latino, assim como o problema original. E como tive dores de cabeça por causa desse primeiro exercício, e faltava apenas uma hora e meia para terminar a prova, dei por satisfeito mais um ano brincando de programar.
