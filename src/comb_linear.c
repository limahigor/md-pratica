#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/comb_linear.h"
#include "../includes/md_module.h"

struct congru_solucao_s{
	int solucao, mod, max;
	int *conjunto;
};

struct congru_valores_s{
	int b, mod;
};

struct resto_chines{
	struct congru_valores_s congruencia;
	struct resto_chines *next;
};

void create_resto_list(chines *list){
    chines aux;

    if(!list){
        printf("Erro ponteiro invalido!\n");
        exit(1);
    }

    aux = malloc(sizeof(*aux));

    if(!aux){
        printf("Erro alocacao de memoria!\n");
        exit(1);
    }

    memset(aux, 0, sizeof(*aux));

    *list = aux;
}

void create_congru_solucao(solucao *list){
    solucao aux;

    if(!list){
        printf("Erro ponteiro invalido!\n");
        exit(1);
    }

    aux = malloc(sizeof(*aux));

    if(!aux){
        printf("Erro alocacao de memoria!\n");
        exit(1);
    }

    memset(aux, 0, sizeof(*aux));

    *list = aux;
}

int in_mod(int x, int y){
	int *resul;
	int inverso;
	resul = (int *)malloc(sizeof(int)*2);

	if(x == 1)
		return x;
	
	if(!(mdc_euclides(x, y) == 1))
		return 0;
	
	resul = comb_linear_mdc(x, y);
	
	inverso = *(resul + 0);
	int teste = *(resul + 1);
	
	while(inverso < 0){
		inverso += y;
	}
	
	while(inverso > y){
		inverso -= y;
	}
	
	free(resul);
	
	return inverso;
}

int resto_chines(chines congruencia, int max){
	int *array_m, *array_m1, *array_m2;
	int mod_total = 1;
	int produto = 0;
	chines aux1;

	aux1 = congruencia;
	for(int c = 0; c < max-1; c++){
		int m1, m2, mdc;

		m1 = aux1->congruencia.mod;
		m2 = aux1->next->congruencia.mod;
		mdc = mdc_euclides(m1, m2);

		if(mdc != 1)
			return 0;

		aux1 = aux1->next;
	}

	array_m = (int *)malloc(sizeof(int)*max);
	array_m1 = (int *)malloc(sizeof(int)*max);
	array_m2 = (int *)malloc(sizeof(int)*max);

	aux1 = congruencia;
	for(int c = 0; c < max; c++){
		chines aux2 = congruencia;
		int temp = 1;

		while(aux2->next != NULL){
			if(aux1->congruencia.mod != aux2->congruencia.mod)
				temp *= aux2->congruencia.mod;

			aux2 = aux2->next;
		}
		*(array_m + c) = temp;
		aux1 = aux1->next;
	}

	aux1 = congruencia;
	for(int c = 0; c < max; c++){
		*(array_m1+c) = *(array_m + c) % aux1->congruencia.mod;
		aux1 = aux1->next;
	}

	aux1 = congruencia;

	for(int c = 0; c < max; c++){
		int x;
		x = *(array_m1+c);
	}

	for(int c = 0; c < max; c++){
		int inv, x, y;

		x = *(array_m1+c);
		y = aux1->congruencia.mod;
		inv = in_mod(x, y);

		*(array_m2+c) = inv;

		aux1 = aux1->next;
	}

	aux1 = congruencia;
	for(int c = 0; c < max; c++){
		int b, m, inverso;

		b = aux1->congruencia.b;
		m = *(array_m + c);
		inverso = *(array_m2 + c);

		mod_total *= aux1->congruencia.mod;
		produto += (b * m * inverso);

		aux1 = aux1->next;
	}

	produto = produto % mod_total;

	return produto;
}

solucao congruencia_generica(int x, int y, int z){
	int mdc, inv, sol;
	int *array;
	solucao conjunto;

	mdc = mdc_euclides(x, z);

	if(!(y % mdc == 0))
		return 0;

	x = x/mdc;
	y = y/mdc;
	z = z/mdc;

	inv = in_mod(x, z);

	sol = inv*y;

	if(sol > z)
		sol = sol%z;

	create_congru_solucao(&conjunto);
	array = (int *)malloc(sizeof(int)*mdc);

	conjunto->solucao = sol;
	conjunto->max = mdc;
	conjunto->mod = z;

	for(int c = 0; c < mdc; c++){
		*(array+c) = (sol + (z * c));
	}

	conjunto->conjunto = array;

	return conjunto;
}

int* comb_linear_mdc(int num1, int num2){
	int *array, *array2, *resul;
	int temp, x, y;
	int qnt = 0, qnt2 = 0, qnt3;

	if(num1 == 1){
		x = 0;
		y = 1;
		return 0;
	}

	if(num2 == 1){
		x = 1;
		y = 0;
		return 0;
	}

	array = (int*)malloc(sizeof(int));
	array2 = (int*)malloc(sizeof(int)*2);

	do{
		*(array+qnt) = num1/num2;
		qnt++;
		array = realloc(array, sizeof(int)*(qnt+1));

		temp = num2;
		num2 = num1%num2;
		num1 = temp;
	}while(num1%num2);

	qnt3 = qnt-2;

	*array2 = 1;
	*(array2+1) = *(array+(qnt-1));
	qnt--;
	qnt2 = 2;

	for(int c = qnt-1; c >= 0; c--){	
		array2 = realloc(array2, sizeof(int) * (++qnt2));	
		
		int temp1 = *(array + c);
		int temp2 = *(array2 + (qnt2 - 2));
		int temp3 = *(array2 + (qnt2 - 3));
		
	*(array2+(qnt2-1)) = (temp1 * temp2) + temp3;
	}

	y = *(array2+(qnt2 - 1));

	if(qnt3 % 2 == 0){
		x = *(array2+(qnt2 - 2)) * (-1);
		y = *(array2+(qnt2 - 1));
	}else{
		x = *(array2+(qnt2 - 2));
		y = *(array2+(qnt2 - 1)) * (-1);
	}

	free(array);
	free(array2);

	resul = (int *)malloc(sizeof(int)*2);

	*(resul+0) = x;
	*(resul+1) = y;

	return resul;
}

//funcoes auxiliares

int comb_get_max(solucao list){
	return list->max;
}

int comb_get_mod(solucao list){
	return list->mod;
}

int comb_get_solucao(solucao list){
	return list->solucao;
}

int* comb_get_conjunto(solucao list){
	return list->conjunto;
}

void chines_preencher(chines list, int *array1, int *array2, int max){
	chines aux = list;

	for(int c = 0; c < max; c++){
		chines temp;

		aux->congruencia.b = *(array1+c);
		aux->congruencia.mod = *(array2+c);

		create_resto_list(&temp);
		aux->next = temp;
		aux = aux->next;
	}
}