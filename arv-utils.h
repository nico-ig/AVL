/* 
 * Feito por Nico Ramos - GRR20210574 
 */

#ifndef _ARVUTILS_
#define _ARVUTILS_

#include "arv.h"

/* Retorna o sucessor do no */
t_arv *sucessor(t_arv *no);

/* Retorna o antecessor do no */
t_arv *antecessor(t_arv *no);

/* Retorna 1 se o no for filho do pai
 * e 0 caso contrario */
int ehFilho(t_arv *pai, t_arv *no);

/* Retorna 1 se o no for o filho da esquerda do pai
 * e 0 caso contrario */
int filhoEsq(t_arv *no);

/* Retorna 1 se o no for o filho da direita do pai
 * e 0 caso contrario */
int filhoDir(t_arv *no);

/* Faz o ponteiro do pai do no para o no apontar para NULL */
void nullPai(t_arv *no);

/* Retorna o fb do no, em caso de NULL retorna -1 */
int fb(t_arv *no);

/* Calcula o novo fb do no,
 * sera o maior fb entre os filhos mais um */
int calculaFB(t_arv *no);

#endif
