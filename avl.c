/* 
 * Feito por Nico Ramos - GRR20210574 
 */

#include <stdlib.h>

#include "avl.h"
#include "arv-utils.h"

/* Enum para os casos de desbalanceamento */
typedef enum caso { zigzig, zagzag, zigzag, zagzig, igual } t_caso;

/* -------------------- Funcoes de rotacao/transplante ---------------------- */

/* Funcao que faz a rotacao a direita do no,
 * vira o filho da direita do filho da esquerda */
void rotDir(t_arv **raiz, t_arv *x)
{
  t_arv *y;
    
  /* y eh o filho da esquerda de x */
  y = x->esq;

  /* A arvore da direita de y vira a arvore da esquerda de x */
  x->esq = y->dir;

  /* Se y tem arvore da direita, x vira o pai dela */
  if ( y->dir )
    y->dir->pai = x;
    
  /* Pai de x vira pai de y */
  y->pai = x->pai;

  /* Se x for raiz, y vira a raiz */
  if ( !x->pai )
    *raiz = y;
  
  else /* x nao eh raiz */
  {
    /* y vira filho da direita do pai de x */
    if ( filhoDir(x) )
      x->pai->dir = y;

    /* y vira filho da esquerda do pai de x */
    else
      x->pai->esq = y;
  }

  /* x vira filho da direita de y */
  y->dir = x;

  /* y vira pai de x */
  x->pai = y;
}

/* Funcao que faz a rotacao a esquerda do no,
 * vira o filho da esquerda do filho da direita */
void rotEsq(t_arv **raiz, t_arv *x)
{
  t_arv *y;
    
  /* y eh o filho da direita de x */
  y = x->dir;

  /* Arvore da esquerda de y vira arvore da esquerda de x */
  x->dir = y->esq;

  /* Se y tem arvore da esquerda, x vira o pai dela */
  if ( y->esq )
    y->esq->pai = x;

  /* Pai de x vira pai de y */
  y->pai = x->pai;

  /* Se x for raiz, y vira a raiz */
  if ( !x->pai )
    *raiz = y;
    
  else /* x nao eh raiz */
  {
    /* y vira o filho da esquerda do pai de x */
    if ( filhoEsq(x) )
        x->pai->esq = y;

    /* y vira o filho da direita do pai de x */
    else
      x->pai->dir = y;
  }

  /* x vira o filho da esquerda de y */
  y->esq = x;

  /* y vira o pai de x */
    x->pai = y;
}

/* ----------------------- Funcoes de balanceamento ------------------------- */

/* Funcao que retorna qual o caso de desbalanceamento 
 * dos filhos*/
t_caso casoBal(t_arv *no)
{
  int fb_esq, fb_dir;
  t_arv *f_esq, *f_dir;

  f_esq = no->esq;
  f_dir = no->dir;

  fb_esq = fb(f_esq);
  fb_dir = fb(f_dir);

  /* Esta balanceada */
  if ( abs(fb_dir - fb_esq) <= 1 )
    return igual;

  /* Direita pesada */
  if ( fb_dir > fb_esq )
  {
    if ( fb(f_dir->dir) >= fb(f_dir->esq) )
      return zigzig;
    
    return zigzag; 
  } 
  
  /* Esquerda pesada */
  if ( fb(f_esq->esq) >= fb(f_esq->dir) )
    return zagzag;

  return zagzig;
}

t_arv *balanceiaAVL(t_arv **raiz, t_arv *no)
{
  t_caso caso;

  /* No nao eh a raiz */
  if ( no )
  {
    switch (caso = casoBal(no))
    {
      case zigzig:
        rotEsq(raiz, no);
        break;

      case zagzag:
        rotDir(raiz, no);
        break;

      case zigzag:
        rotDir(raiz, no->dir);
        rotEsq(raiz, no);

        /* Recalcula o fb do filho da direita 
         * Virou o irmao da direita do no */
        no->pai->dir->fb = calculaFB(no->pai->dir);
        break;

      case zagzig:
        rotEsq(raiz, no->esq);
        rotDir(raiz, no);
        
        /* Recalcula o fb do filho da esquerda
         * Virou o irmao da esquerda do no */
        no->pai->esq->fb = calculaFB(no->pai->esq);
        break;

      /* A arvore esta balanceada */
      default:
        break;
    }

    /* Calcula o fb do no apos as rotacoes */
    no->fb = calculaFB(no);
    
    /* Balanceia o nivel anterior da AVL */
    return balanceiaAVL(raiz, no->pai);
  }

  /* A raiz pode ter mudado */
  return *raiz;
}

/* --------------------------- Funcoes de insercao -------------------------- */

t_arv *insereAVL(t_arv **raiz, int chave)
{
  t_arv *no; 
  
  /* Testa se conseguiu criar o no */
  if ( ! (no = insereBST(raiz, raiz, chave)) )
    return NULL;

  /* Se conseguiu criar o no faz o balanceamento */
  balanceiaAVL(raiz, no);

  return no;
}

/* -------------------------- Funcoes de remocao ---------------------------- */

t_arv *removeAVL(t_arv **raiz, int chave)
{
  t_arv *pai;

  /* Se nao achou o no retorna NULL */
  if ( ! (pai = removeBST(raiz, chave)) )
    return NULL;

  /* Se removeu o no balanceia a arvore */
  balanceiaAVL(raiz, pai);

  return pai;
}


