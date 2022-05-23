#ifdef __unix__         
    #include <stdlib.h>

#elif defined(_WIN32) || defined(WIN32) 

   #define OS_Windows

   #include <windows.h>

#endif

#include <stdio.h>
#include "../includes/md_module.h"
#include "../includes/comb_linear.h"
#include "../includes/fatora_module.h"

void menu(){
    printf("--------------------- AULA PRATICA MD ----------------------\n");
    printf("[1] Determinar se e primo.\n");
    printf("[2] Sequencia de primos em determinado tempo.\n");
    printf("[3] Decompor um numero em seus fatores primos.\n");
    printf("[4] MDC e MMC por decomposicao.\n");
    printf("[5] MDC com Algoritmo de Euclides.\n");
    printf("[6] Coeficientes na combinacao linear.\n");
    printf("[7] Inverso de a mod b.\n");
    printf("[8] Solucao de congruencia.\n");
    printf("[9] Teorema do Resto Chines.\n");
    printf("[10] Sair\n");
}

_Bool opcao(){
    int num1, num2, num3;
    int escolha;

    scanf("%d", &escolha);

    if(escolha == 1) {
        printf("Defina um valor:\n");
        scanf("%d", &num1);

        printf("\n");

        if(isprime(num1))
            printf("Eh primo!\n");
        else
            printf("Nao eh primo!\n");

    }else if (escolha == 2) {
        printf("Digite o intervalo de tempo:\n");
        scanf("%d", &num1);
        maior_primo(num1);
    }else if (escolha == 3) {
        unsigned int num, max1;
        unsigned int *array1;
        decom_t num_decomp;

        printf("Defina um valor:\n");
        scanf("%i", &num1);

        printf("\n");

        array1 = (int *)malloc(sizeof(int));
        max1 = decompor(num1, array1, 0);
        num_decomp = contar_indices(array1, max1);

        printar(num_decomp);

        free(array1);
        destroy_decom_t(num_decomp);
    }else if (escolha == 4) {
        mdc_mmc_t list;
        unsigned int *array1;

        printf("Defina dois valores:\n");

        scanf("%d%d", &num1, &num2);
        list = mdc_mmc_decomp(num1, num2);

        printf("\n");
        printf("%i | ", num1);
        printar_list1(list);

        printf("%i | ", num2);
        printar_list2(list);

        printf("MDC = ");
        printar_list_mdc(list);

        printf("MMC = ");
        printar_list_mmc(list);
        printf("MDC(%i, %i) = %i\n", num1, num2, get_mdc(list));
        printf("MMC(%i, %i) = %i\n\n", num1, num2, get_mmc(list));

        destroy_mdc_mmc_t(list);

    } else if (escolha == 5) {
        printf("Defina dois valores:\n");
        scanf("%d%d", &num1, &num2);
        printf("MDC(%d, %d) = %d\n", num1, num2, mdc_euclides(num1, num2));

    } else if (escolha == 6) {
        unsigned int *array1;

        printf("Defina dois valores:\n");

        array1 = (int *)malloc(sizeof(int) * 2);

        scanf("%d%d", &num1, &num2);
        array1 = comb_linear_mdc(num1, num2);

        printf("\nMDC(%d, %d) = %d * %d  +  %d * %d\n", num1, num2, array1[0], num1, array1[1], num2);
        free(array1);

    }else if (escolha == 7) {
        int inverso;
        printf("Defina dois valores:\n");
        scanf("%d%d", &num1, &num2);

        inverso = in_mod(num1, num2);

        if(!inverso){
            printf("\nNao existe!\n");
        }else
            printf("\nInverso %i mod %i = %d\n", num1, num2, inverso);

    } else if (escolha == 8){
        int solu, mod, max;
        int *conjunto;
        solucao list;
        
        printf("Defina tres valores:\n");
        scanf("%d%d%d", &num1, &num2, &num3);

        create_congru_solucao(&list);
        list = congruencia_generica(num1, num2, num3);

        solu = comb_get_solucao(list);
        mod = comb_get_mod(list);
        max = comb_get_max(list);

        conjunto = (int *)malloc(sizeof(int)*max);
        conjunto = comb_get_conjunto(list);

        printf("Solucao Geral: %i + %i*k\n", solu, mod);
        if(max == 1)
            printf("MDC = 1, solucao unica!\n");

        printf("{ ");
        for(int c = 0; c < max; c++){
            printf("%i", *(conjunto+c));
            if(c < max-1)
                printf(", ");
        }
        printf(" }\n");

    } else if (escolha == 9) {
        int x;
        chines list;
        int *array1, *array2;
        create_resto_list(&list);

        printf("Numero de congruencias(min 3): ");
        scanf("%i", &num1);

        if(num1 < 3){
            printf("Invalido!");
            return 1;
        }

        array1 = (int *)malloc(sizeof(int)*num1);
        array2 = (int *)malloc(sizeof(int)*num1);

        for(int c = 0; c < num1; c++){
            int temp;

            printf("b%i: ", c+1);
            scanf("%i", &temp);
            *(array1+c) = temp;

            printf("mod%i: ", c+1);
            scanf("%i", &temp);
            *(array2+c) = temp;
        }

        printf("\n");
        for(int c = 0; c < num1; c++){
            printf("x cong. %i mod %i", *(array1+c), *(array2+c));
            if(c < num1 - 1)
                printf(" | ");
        }
        printf("\n");
        
        chines_preencher(list, array1, array2, num1);
        x = resto_chines(list, num1);
        printf("\nx = %i\n\n", x);
    }

    else if(escolha == 10)
        return 0;
    else
        printf("Opcao invalida");

    printf("Aperte qualquer tecla para voltar...");
    getchar();
    getchar();
    return 1;
}

int main(){
    _Bool loop = 1;

    while(loop){
        #ifdef OS_Windows
            system("cls");
        #else
            system("clear");
        #endif

        menu();
        loop = opcao();
    }
    
    return 0;
}