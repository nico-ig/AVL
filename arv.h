/* 
 * Feito por Nico Ramos - GRR20210574 
 */

#ifndef _ARV_
#define _ARV_

/* Struct que defino cada no da arvore, com ponteiro para o pai */
typedef struct arv
{
  int chave;                    /* Chave que identifica o no */
  int fb;                       /* Fator de balanceamento do no */
  struct arv *pai, *dir, *esq;  /* Ponteiros para o pai e filhos */
} t_arv;

/* Insere um no na arvore,
 * Retorna um ponteiro para ele em caso de sucesso e NULL caso contrario */
t_arv *insereBST(t_arv **raiz, t_arv **no, int chave);

/* Em caso de sucesso retorna um ponteiro para o no com a chave
 * e NULL caso nao encontre */
t_arv *buscaBST(t_arv *no, int chave);

/* Remove o no identificado pela chave 
 * Em caso de sucesso retorna a nova raiz se o no for a raiz ou o pai se nao
 * Retorna NULL caso o no nao esteja na arvore */
t_arv *removeBST(t_arv **raiz, int chave);

/* Imprime a arvore em ordem crescente
 * Imprime a chave do no e a altura dele */
void imprime(t_arv *no, int h);

/* Destroi a arvore */
void destroi(t_arv *no);

#endif
