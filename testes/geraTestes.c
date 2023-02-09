#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#define QTD_OP 10
#define QTD_I 7

int alet(int ini, int fim)
{
  return (ini + (rand() % (fim - ini + 1)));
}

char converteOP(int op)
{
  if ( op <= QTD_I )
    return 'i';

  return 'r';
}

int main()
{
  int n;
  char op;

  srand(time(0));

  for ( int i = 0; i < QTD_OP; i++ )
  {
    op = converteOP(alet(1, 10));
    n = alet(0, QTD_OP);
  
    printf("%c %d\n", op, n);
  }

  return 0;
}
