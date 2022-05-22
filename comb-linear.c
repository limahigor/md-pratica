#include <stdio.h>
#include <stdlib.h>

int main(){
	int *m, *n, *euclides;
	unsigned int num1, num2, x, y;
	int m_qnt, n_qnt2, e_qnt;
	
	scanf("%i %i",  &num1, &num2);

	m = (int*)malloc(sizeof(int)*2);
	n = (int*)malloc(sizeof(int)*2);
	euclides = (int*)malloc(sizeof(int));
	e_qnt = 0;

	while(num2){
		unsigned int temp;

		*(euclides + e_qnt) = num1/num2;
		printf("T: %i ", num1/num2);
		e_qnt++;
		euclides = realloc(euclides, sizeof(int) * (e_qnt+1));

    	temp = num1%num2;
    	num1 = num2;
    	num2 = temp;
    };
    
    //inicializando variaveis
    *(m+0) = 1;
	*(m+1) = 0;

    *(n+0) = 0;
    *(n+1) = 1;

    m_qnt = 2;
    m_qnt = 2;
    //-----------------------

    
    
    free(m);
    free(n);
    free(euclides);
    
    return 0;
}