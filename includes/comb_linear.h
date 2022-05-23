#ifndef COMB_LINEAR_MODULE_H
#define COMB_LINEAR_MODULE_H

typedef struct resto_chines *chines;
typedef struct congru_solucao_s *solucao;

solucao congruencia_generica(int x, int y, int z);
int in_mod(int x, int y);
int resto_chines(chines congruencia, int max);
int* comb_linear_mdc(int x, int y);

void create_congru_solucao(solucao *list);
void create_resto_list(chines *list);


//funcoes auxiliares
int comb_get_max(solucao list);
int comb_get_mod(solucao list);
int comb_get_solucao(solucao list);
int* comb_get_conjunto(solucao list);
void chines_preencher(chines list, int *array1, int *array2, int max);

#endif