/** Imprime uma tabela alinhando a primeira coluna à esquerda e a segunda 
coluna à direita, respeitando o tamanho do maior campo da primeira coluna.
*/
void printf_string_align_variable_size()
{
	struct GitBranches branches[2];
	char* cr;
	size_t len1, len2, maxlen;

	printf("master branch: ");
	fgets(branches[0].name, sizeof(branches[0].name), stdin);
	if (cr = strrchr(branches[0].name, '\n'))
		*cr = 0;
	printf("number of commits: ");
	scanf("%d", &branches[0].commits);
	len1 = strlen(branches[0].name);

	clean_stdin_buffer();

	printf("slave branch: ");
	fgets(branches[1].name, sizeof(branches[1].name), stdin);
	if (cr = strrchr(branches[1].name, '\n'))
		*cr = 0;
	printf("number of commits: ");
	scanf("%d", &branches[1].commits);
	len2 = strlen(branches[1].name);

	maxlen = max(len1, len2);
	printf("\n%-*s %s\n", maxlen, "branches", "commits");
	printf("%-*s %d\n", maxlen, branches[0].name, branches[0].commits);
	printf("%-*s %d\n", maxlen, branches[1].name, branches[1].commits);
}

