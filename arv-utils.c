/* 
 * Feito por Nico Ramos - GRR20210574 
 */

#include <stdlib.h>

#include "arv-utils.h"

t_arv *sucessor(t_arv *no)
{
  if ( ! no->esq )
    return no;

  return sucessor(no->esq);
}

t_arv *antecessor(t_arv *no)
{
  if ( ! no->dir )
    return no;

  return antecessor(no->dir);
}

int ehFilho(t_arv *pai, t_arv *no)
{
  if ( no->pai == pai )
    return 1;

  return 0;
}

int filhoEsq(t_arv *no)
{
  if ( no == no->pai->esq )
    return 1;

  return 0;
}

int filhoDir(t_arv *no)
{
  if ( no == no->pai->dir )
    return 1;

  return 0;
}

void nullPai(t_arv *no)
{
  if ( filhoEsq(no) )
    no->pai->esq = NULL;
  
  else
    no->pai->dir = NULL;
}

int fb(t_arv *no)
{
  if ( no )
    return no->fb;

  /* Se for NULL */
  return -1;
}

int calculaFB(t_arv *no)
{
  int fb_esq, fb_dir;

  fb_esq = fb(no->esq);
  fb_dir = fb(no->dir);

  /* Caminho na esquerda eh maior */
  if ( fb_esq > fb_dir )
    return fb_esq+1;

  return fb_dir+1;
}
