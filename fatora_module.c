#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fatora_module.h"
#include "md_module.h"

struct decom_h{
    unsigned int num;
    unsigned int indices;
    struct decom_h *next;
};

struct mdc_mmc_h{
    unsigned int mmc, mdc;
    struct decom_h *list1, *list2, *list_mmc, *list_mdc;
};

#define LINK(next, temp){\
    create_decom_t(&next);\
    temp->next = next;\
    temp = next;\
}

#define ADD(array, size, n, valor){\
    *(array + n) = (valor);\
    n++;\
    array = realloc(array, n*sizeof(int));\
}

void create_mmc_mdc_t(mdc_mmc_t *list){
    mdc_mmc_t aux;

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

void create_decom_t(decom_t *list){
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

void destroy_mdc_mmc_t(mdc_mmc_t list){
    destroy_decom_t(list->list1);
    destroy_decom_t(list->list2);
    destroy_decom_t(list->list_mmc);
    destroy_decom_t(list->list_mdc);
    free(list);
}

void destroy_decom_t(decom_t list){
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

    create_decom_t(&num_decomp);

    temp = num_decomp;

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

decom_t ver_indice(decom_t list1,
                   decom_t list2,
                   unsigned int verifica){

    unsigned int count;
    decom_t temp1, temp2, temp3, total, next;

    create_decom_t(&total);

    temp1 = list1;
    temp2 = list2;
    temp3 = total;

    while(temp1->next != NULL){
        count = 0;

        while(temp2->next != NULL){

            if(temp1->num == temp2->num){
                temp3->num = temp2->num;

                if(temp2->indices > temp1->indices){
                    if(verifica)
                        temp3->indices = temp2->indices;
                    else
                        temp3->indices = temp1->indices;
                }
                else{
                    if(verifica)
                        temp3->indices = temp1->indices;
                    else
                        temp3->indices = temp2->indices;
                }

                count++;
            }

            temp2 = temp2->next;
        }

        if(!count){
            temp3->num = temp1->num;
            if(verifica){
                temp3->indices = temp1->indices;
            }
            else{
                temp3->indices = 0;
            }
        }

        LINK(next, temp3);

        temp1 = temp1->next;
    }

    temp1 = list1;
    temp2 = list2;

    while(temp2->next != NULL){
        count = 0;
        while(temp1->next != NULL){
            if(temp2->num == temp1->num){
                count++;
            }
            temp1 = temp1->next;
        }

        if(!count){
            temp3->num = temp2->num;

            if(verifica)
                temp3->indices = temp2->indices;
            else
                temp3->indices = 0;

            LINK(next, temp3);
        }

        temp2 = temp2->next;
    }

    return total;
}

mdc_mmc_t mdc_mmc_decomp(int num1, int num2){
    unsigned int max1, max2, mdc, mmc;
    unsigned int *array1, *array2;
    decom_t array1_indices, array2_indices, list_mdc, list_mmc, list_total;
    mdc_mmc_t calc_result;

    mdc = 1;
    mmc = 1;

    array1 = (int *)malloc(sizeof(int));
    array2 = (int *)malloc(sizeof(int));
    create_decom_t(&list_mmc);
    create_decom_t(&list_mdc);
    create_mmc_mdc_t(&calc_result);

    max1 = decompor(num1, array1, 0);
    max2 = decompor(num2, array2, 0);

    array1_indices = contar_indices(array1, max1);
    array2_indices = contar_indices(array2, max2);

    list_mdc = ver_indice(array1_indices, array2_indices, 0);
    list_total = list_mdc;
    
    while(list_total->next != NULL){
        mdc *= pow(list_total->num, list_total->indices);
        list_total = list_total->next;
    }

    list_mmc = ver_indice(array1_indices, array2_indices, 1);
    list_total = list_mmc;

    while(list_total->next != NULL){
        mmc *= pow(list_total->num, list_total->indices);
        list_total = list_total->next;
    }

    calc_result->mmc = mmc;
    calc_result->mdc = mdc;
    calc_result->list1 = array1_indices;
    calc_result->list2 = array2_indices;
    calc_result->list_mmc = list_mmc;
    calc_result->list_mdc = list_mdc;

    free(array1);
    free(array2);

    return calc_result;
}

//funções para testes
void printar(decom_t list){
    while(list->next != NULL){
        printf(" %i ^ %i | ", list->num, list->indices);
        list = list->next;
    }
    printf("\n");
}

void printar_list1(mdc_mmc_t list){
    printar(list->list1);
}

void printar_list2(mdc_mmc_t list){
    printar(list->list2);
}

void printar_list_mmc(mdc_mmc_t list){
    printar(list->list_mmc);
}

void printar_list_mdc(mdc_mmc_t list){
    printar(list->list_mdc);
}

unsigned int get_mdc(mdc_mmc_t list){
    return list->mdc;
}

unsigned int get_mmc(mdc_mmc_t list){
    return list->mmc;
}