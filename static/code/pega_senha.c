#include <stdio.h>
#include <conio.h>


struct funcionario
{
  char senha[100];
};

int main()
{
  int c, pos = 0;
  struct funcionario cfuncionario;

  printf("\nSenha do usuario: \n");

  //Adiciona * nos valores digitados na senha.
  do
  {
    c = _getch();
    if (isprint(c))
    {
      cfuncionario.senha[pos++] = c;
      printf("%c", '*');
    }
    else if (c == 8 && pos)
    {
      cfuncionario.senha[pos--] = '\0';
      printf("%s", "\b \b");
    }
  } while (c != 13 || pos == 0);

  fseek(stdin, 0, SEEK_END);
}
