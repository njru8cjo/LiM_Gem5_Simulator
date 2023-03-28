#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{    
    /* variable declaration */
    int N = 10;
    int i;
    int *vector = (int *)malloc(N * sizeof(int));
    int max;
    int min;
    
    /* fill vector */
    for(i=0; i<N; i++){    
    	vector[i] = i*13467;
    }

    for(int i = 0; i < N; i++)
    {
        printf("vector[%d] x= %08x, d=%d\n", i, vector[i], vector[i]);
    }
    printf("=======================================\n");


    /* MAX operation */
    max = vector[0];

    for(i=1; i<N; i++){
    	if(vector[i] > max){
		    max = vector[i];
        }    	
    }

   /* MIN operation */
    min = vector[0];

    for(i=1; i<N; i++){
    	if(vector[i] < min){
		    min = vector[i];
        }    	
    }
    
    for(int i = 0; i < N; i++)
    {
        printf("vector[%d] x= %08x, d=%d\n", i, vector[i], vector[i]);
    }

    printf("max : %d , x = %08x\n", max, max);
    printf("min : %d , x = %08x\n", min, min);
       
    return EXIT_SUCCESS;
}
