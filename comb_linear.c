#include <stdio.h>
#include <stdlib.h>
#include "comb_linear.h"
#include "md_module.h"

struct congruencia_s{
	int x, y, z;
};

struct resto_chines{
	congruencia_s;
	struct resto_chines *next;
};

int inverso(int x, int y){
	int *resul;
	int inverso;
	resul = (int *)malloc(sizeof(int)*2);
	
	if(!(mdc_euclides(x, y) == 1))
		return -1;
	
	resul = comb_linear_mdc(x, y);
	
	inverso = *(resul + 0);
	
	while(inverso < 0)
		inverso += y;
	
	while(inverso > y)
		inverso -= y;
	
	free(resul);
	
	return inverso;
}

int resto_chines();

int comb_linear_generica(int x, int y, int z){
	
}

int* comb_linear_mdc(int x, int y){
	int *array, *array2, *resul;
	int num1, num2, temp;
	int qnt = 0, qnt2 = 0, qnt3;
	
	resul = (int*)malloc(sizeof(int) * 2);
	
	scanf("%i %i",  &num1, &num2);
	
	if(num1 == 1){
		x = 0;
		y = 1;
		
		*(resul + 0) = x;
		*(resul + 1) = y;
		return resul;
	}
	
	if(num2 == 1){
		x = 1;
		y = 0;
	   
		*(resul + 0) = x;
		*(resul + 1) = y;
		return 0;
	}
	
	array = (int*)malloc(sizeof(int));
	array2 = (int*)malloc(sizeof(int)*2);
	
    do{
    	*(array+qnt) = num1/num2;
    	qnt++;
    	array = realloc(array, sizeof(int)*(qnt+1));
    	
        temp = num2;
        num2 = num1 % num2;
        num1 = temp;
    }while(num1 % num2);
    
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
    
    if(qnt3 % 2 == 0){
       x = *(array2+(qnt2 - 2)) * (-1);
       y = *(array2+(qnt2 - 1));
    }else{
       x = *(array2+(qnt2 - 2));
       y = *(array2+(qnt2 - 1)) * (-1);
    }
    
    free(array);
    free(array2);
	
	resul = (int*)malloc(sizeof(int) * 2);
	*(resul + 0) = x;
	*(resul + 1) = y;
    
    return resul;
}