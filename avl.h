/* 
 * Feito por Nico Ramos - GRR20210574 
 */

#ifndef _AVL_
#define _AVL_

#include "arv.h"

/* Balanceia a arvore a partir do no em direcao a raiz
 * Retorna a raiz */
t_arv *balanceiaAVL(t_arv **raiz, t_arv *no);

/* Funcao que insere um no na arvore. 
 * Retorna um ponteiro para o no inserido em caso de sucesso 
 * e NULL caso contrario */
t_arv *insereAVL(t_arv **raiz, int chave);

/* Procura pelo no com a chave, se achar remove ele 
 * Retorna o pai do no removido, para poder balancear */
t_arv *removeAVL(t_arv **raiz, int chave);

#endif
