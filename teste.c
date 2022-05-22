#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "md_module.h"

#define PRIMO    1
#define N_PRIMO  0

struct decom_h{
    unsigned int num;
    unsigned int indices;
    struct decom_h *next;
};

#define LINK(next, temp){\
    create_list(&next);\
    temp->next = next;\
    temp = next;\
}

#define ADD(array, size, n, valor){\
    *(array + n) = (valor);\
    n++;\
    array = realloc(array, n*sizeof(int));\
}

unsigned int isprime(unsigned long int num){
    unsigned long int raizq;
 
    if(num < 3){
        if(num < 2)
            return N_PRIMO;
        return PRIMO; 
    }
 
    if(num%2 == 0)
        return N_PRIMO;
 
    raizq = sqrt(num);
 
    for(int c = 3; c <= raizq; c += 2){
        if(num % c == 0)
            return N_PRIMO;
    }
 
    return PRIMO;
}

void create_list(decom_t *list){
    decom_t aux;

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

    aux->num = 0;
    aux->indices = 0;

    *list = aux;
}

void destroy_list(decom_t list){
    decom_t temp;

    while(list->next != NULL){
        temp = list->next;
        free(list);
        list = temp;
    }
}

int decompor(unsigned int num, int *array, int n){
    if(num > 1){
        if(num % 2 == 0){
            ADD(array, n*sizeof(int), n, 2);
            return decompor(num/2, array, n);
        }

        for(int c = 3; c <= num; c += 2){
            if(isprime(c)){
                if(num % c == 0){
                    ADD(array, n*sizeof(int), n, c);
                    return decompor(num/c, array, n);
                }
            }
        }
    }

    return n;
}

decom_t contar_indices(int *array, int max){
    decom_t num_decomp, temp, next;

    printf("TESTE1\n");

    create_list(&num_decomp);

    temp = num_decomp;

    printf("TESTE2\n");

    for(int c = 0; c < max; c++){
        int verifica = 1;

        for(int i = 0; i < c; i++){
            if(*(array+c) == *(array+i))
                verifica = 0;
        }

        if(verifica){
            temp->num = *(array+c);
            temp->indices = 1;

            for(int j = (c+1); j < max; j++){
                if(*(array+c) == *(array+j)){
                    temp->indices++;
                }
            }

            LINK(next, temp);
        }
    }

    return num_decomp;
}

int main(){
    unsigned int num1, num2, max;
    unsigned int *array;

    array = (int *)malloc(sizeof(int));

    decom_t num_fatorado;

    scanf("%i", &num1);

    max = decompor(num1, array, 0);

    //for(int c = 0; c < max; c++);

    num_fatorado = contar_indices(array, max);

    printf("N: %i I: %i\n", num_fatorado->num, num_fatorado->indices);
    printf("N: %i I: %i\n", num_fatorado->next->num, num_fatorado->next->indices);

    return 0;
}