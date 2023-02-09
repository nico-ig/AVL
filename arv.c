/* 
 * Feito por Nico Ramos - GRR20210574 
 */

#include <stdio.h>
#include <stdlib.h>

#include "arv.h"
#include "avl.h"
#include "arv-utils.h"

/* Enum para os casos de remocao de um no */
typedef enum casoRm { folha, filho_dir, filho_esq, dois_filhos } t_casoRm;

/* ------------------------- Funcoes de insercao ---------------------------- */

/* Cria um no, em caso de sucesso retorna um ponteiro para ele e 
 * NULL caso contrario */
t_arv *criaNo(t_arv **pai, t_arv **p_pai_filho, int chave)
{
  t_arv *no;

  if ( ! (no = malloc(sizeof(t_arv))) )
    return NULL;

  /* Inicia os ponteiros */
  no->chave = chave;
  no->fb = 0;
  no->dir = NULL;
  no->esq = NULL;
  no->pai = *pai;
  
  /* Pai aponta pro filho */
  *p_pai_filho = no;
  
  return no;
}

t_arv *insereBST(t_arv **raiz, t_arv **no, int chave)
{
  t_arv *no_inserido;

  /* Cria o no */
  if ( ! *no )
    no_inserido = criaNo(raiz, no, chave);

  /* Se a chave for maior ou igual insere na direita */
  else if ( (*no)->chave <= chave )
    no_inserido = insereBST(no, &(*no)->dir, chave);
  
  /* Se a chave for menor insere na esquerda */
  else no_inserido = insereBST(no, &(*no)->esq, chave);

  /* Testa se conseguiu criar o no */
  if ( ! no_inserido )
    return NULL;

  return no_inserido;
}

/* --------------------------- Funcoes de busca ----------------------------- */

t_arv *buscaBST(t_arv *no, int chave)
{
  /* A chave nao esta na folha */
  if ( !no )
    return NULL;

  /* Achou o no */
  if ( (chave == no->chave) )
    return no;

  /* A chave esta para a direita */
  if ( chave > no->chave )
    return buscaBST(no->dir, chave);

  /* A chave esta para a esquerda */
  return buscaBST(no->esq, chave);
}

/* --------------------------- Funcoes de remocao --------------------------- */

/* Retorna qual o caso de remocao para o no */
t_casoRm casoRm(t_arv *no)
{
  if ( !no->esq && !no->dir )
    return folha;

  if ( !no->esq && no->dir )
    return filho_dir;

  if ( no->esq && !no->dir )
    return filho_esq;

  return dois_filhos;
}

/* Transplanta o no y para o lugar do no x,
 * Nao altera o pai dos filhos de x */
void transplante(t_arv **raiz, t_arv *x, t_arv *y)
{
  /* x for a raiz, y vira a raiz */
  if ( x == *raiz )
    *raiz = y;

  else /* x nao eh raiz */
  {
    /* y vira o filho da esquerda do pai de x */
    if ( filhoEsq(x) )
      x->pai->esq = y;

    /* y vira o filho da direita do pai de y */
    else
      x->pai->dir = y;
  }
 
  /* Se y nao for NULL o pai dele vira o pai de x */
  if ( y )
    y->pai = x->pai;
}

/* Remove um no que eh folha, apos a remocao o pai aponta para NULL
 * se o no for a raiz a raiz aponta para NULL */
void removeFolha(t_arv **raiz, t_arv *no)
{
  if ( no == *raiz )
    *raiz = NULL;
  
  else
    nullPai(no);
}

/* Funcao que remove um no substituindo ele pelo seu sucessor */
void removePeloSucessor(t_arv **raiz, t_arv *no)
{
  t_arv *suc = sucessor(no->dir);

  if ( ! ehFilho(no, suc) )
  {
    /* Tio do suc passa a ser o pai do filho da direita do suc */
    transplante(raiz, suc, suc->dir);

    /* Sucessor vira pai do filho da direita do no */
    suc->dir = no->dir;
    no->dir->pai = suc;
  }

  /* Sucessor vira filho do pai do no */
  transplante(raiz, no, suc);
  
  /* Sucessor vira pai do filho da esquerda */
  suc->esq = no->esq;
  no->esq->pai = suc;

  /* O pai do suc virou o filho da direita,
   * recalcula o FB */
  if ( suc->dir )
    suc->dir->fb = calculaFB(suc->dir);

  /* Faz o balanceamento na sub-arvore na qual o pai do sucessor eh raiz */
  if ( suc != *raiz )
    balanceiaAVL(&suc->pai, suc);
}

/* Funcao para remover um no com dois filhos
 * Caso o antecessor seja igual ao pai dele substitui o no pelo sucessor 
 * caso contrario substitui pelo antecessor */
void removeDoisFilhos(t_arv **raiz, t_arv *no)
{
  t_arv *ant = antecessor(no->esq);

  /* Testa se o antecessor eh igual ao pai */
  if ( (ant->chave == ant->pai->chave) )
    removePeloSucessor(raiz, no);

  else
  {
    if ( ! ehFilho(no, ant) )
    {
      /* Tio do ant passa a ser o pai do filho da esquerda do ant */
      transplante(raiz, ant, ant->esq);

      /* Antecessor vira pai do filho da esquerda do no */
      ant->esq = no->esq;
      no->esq->pai = ant;
    }

    /* Antecessor vira filho do pai do no */
    transplante(raiz, no, ant);
  
    /* Antecessor vira pai do filho da direita */
    ant->dir = no->dir;
    no->dir->pai = ant;

    /* Removeu um no do lado esquerdo, recalcula o FB */
    if ( ant->esq )
      ant->esq->fb = calculaFB(ant->esq);

    /* Faz o balanceamento da sub-arvore na qual o pai do ant eh raiz */
    if ( ant != *raiz )
      balanceiaAVL(&ant->pai, ant);
  }
}

t_arv *removeBST(t_arv **raiz, int chave)
{
  t_arv *pai, *no;
  t_casoRm caso;

  /* Se encontrou o no remove ele */
  if ( (no = buscaBST(*raiz, chave)) )
  {
    pai = no->pai;

    switch ( caso = casoRm(no) )
    {
      case folha:
        removeFolha(raiz, no);
        break;

      case filho_esq:
        transplante(raiz, no, no->esq);
        break;

      case filho_dir:
        transplante(raiz, no, no->dir);
        break;

      case dois_filhos:
        removeDoisFilhos(raiz, no);
        break;
    }

    free(no);
 
    /* Retorna o pai para fazer o balanceamento */
    if ( pai )
      return pai;
  
    /* O no removido era raiz, retorna a nova raiz */
    return *raiz;
  }

  /* Nao encontrou o no */
  return NULL;
}

/* --------------------------- Funcoes de impressao ------------------------- */

void imprime(t_arv *no, int h)
{
  /* Chegou na folha */
  if ( ! no )
    return;

  imprime(no->esq, h+1);

  printf("%d,%d\n", no->chave, h);

  imprime(no->dir, h+1);
}

/* -------------------- Funcoes de destruicao/encerramento ------------------ */

void destroi(t_arv *no)
{
  if ( ! no )
    return;

  destroi(no->esq);
  destroi(no->dir);
  free(no);
}
