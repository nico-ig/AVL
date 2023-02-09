/* 
 * Feito por Nico Ramos - GRR20210574 
 */

#include <stdio.h>
#include <string.h>

#include "avl.h"

int main()
{
  int n;
  char op;
  t_arv *T = NULL;

  while ( scanf("%c %d", &op, &n) != EOF )
  {
    switch (op)
    {
      case 'i':
        insereAVL(&T, n);
        break;

      case 'r':
        removeAVL(&T, n);
        break;

      case '\n':
        break;

      default:
        fprintf(stderr, "Operacao %c invalida.\n", op);
        break;
    }
  }

  imprime(T, 0);
  destroi(T);
}
