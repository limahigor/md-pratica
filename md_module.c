#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "md_module.h"
#include "fatora_module.h"
 
#define PRIMO    1
#define N_PRIMO  0

#define troca(x, y){\
    __typeof(x) temp = (x);\
    (x) = (y);\
    (y) = (temp);\
}

int coprimo(){
	
}

int mdc_euclides(unsigned int x, unsigned int y){
    if(x < y)
        troca(x, y);
    
    if((x % y) == 0)
        return y;
        
    return mdc_euclides(y, (x % y));
}

void comb_linear(unsigned int x, unsigned int y){
    unsigned int qnt = 0, aux = 0;
    int *array, *result;

    array = (int*)malloc(sizeof(int));
    result = (int*)malloc(sizeof(int)*1);

    while(y){
        unsigned int t;

        if(x%y)
            *(array+qnt) = x/y;

        t = y;
        y = x%y;
        x = t;

        if(y){
            qnt++;
            array = realloc(array, sizeof(int)*qnt);
        }
    }

    printf("TESTE\n");

    for(int c = 0; c < aux; c++)
        printf("%i\n", *(result+aux));

    free(array);
}
 
unsigned int isprime(unsigned long int num){
    unsigned long int raizq;
 
    if(num < 3){
        if(num < 2)
            return N_PRIMO;
        return PRIMO; 
    }
 
    if((num % 2) == 0)
        return N_PRIMO;
 
    raizq = sqrt(num);
 
    for(int c = 3; c <= raizq; c += 2){
        if(num % c == 0)
            return N_PRIMO;
    }
 
    return PRIMO;
}
 
void maior_primo(int intervalo){ //maior primo em 60s
    unsigned long int count;
    count = 3;
    unsigned int start = clock()/CLOCKS_PER_SEC;
    unsigned int stop = 0;

    printf("2\n");
 
    do{
        if(isprime(count))
            printf("%li\n", count);
        count += 2;
        stop = clock()/CLOCKS_PER_SEC;
    }while((stop-start) < intervalo);
}

void mdc_mmc(int num1, int num2){
    mdc_mmc_t resultado;

    resultado = mdc_mmc_decomp(num1, num2);

    //formatando saida
    printf("\n");
    printf("%i  |", num1);
    printar_list1(resultado);

    printf("%i  |", num2);
    printar_list2(resultado);

    printf("MDC |");
    printar_list_mdc(resultado);

    printf("MMC |");
    printar_list_mmc(resultado);
    printf("\n");
    //--------------

    printf("MMC(%i, %i) = %i\n", num1, num2, get_mmc(resultado));
    printf("MDC(%i, %i) = %i\n", num1, num2, get_mdc(resultado));

    destroy_mdc_mmc_t(resultado);
}

int main(){
    unsigned int num1, num2;
 
    scanf("%i %i", &num1, &num2);

    //printf("\n%i\n", mdc_euclides(num1, num2));
    comb_linear(num1, num2);
    
    return 0;
}