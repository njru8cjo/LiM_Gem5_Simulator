#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{    
    /* variable declaration */
    int N = 5, i, mask_or, mask_and, mask_xor;
    int *vector = (int *)malloc(N * sizeof(int));
    int *stand_alone = (int *)malloc(sizeof(int));
    int *final_result = (int *)malloc(sizeof(int));

    /* fill vector */
    for(i=0; i<N; i++){    
    	vector[i] = i*13467;
    }
    *stand_alone = vector[1]+0x768;

    /* OR operation */
    mask_or = 0xF1;
    for(i=0; i<N; i++){
    	vector[i] = vector[i] | mask_or;
    }
    *stand_alone = *stand_alone | mask_or;
    printf("0x%x\n", *stand_alone);

    /* AND operation */
    mask_and = vector[N-1] & 0x8F;
    printf("mask_and = 0x%x\n", mask_and);
    for(i=0; i<N; i++){
    	vector[i] = vector[i] & mask_and;
    }
    *stand_alone = *stand_alone & mask_and;
    printf("0x%x\n", *stand_alone);
  
    /* XOR operation */
    mask_xor = vector[N-2] ^ 0xF0;
    printf("mask_xor = 0x%x\n", mask_xor);
    for(i=0; i<N; i++){
    	vector[i] = vector[i] ^ mask_xor;
    }
    *stand_alone = *stand_alone ^ mask_xor;
    printf("0x%x\n", *stand_alone);

    *final_result = ~vector[N-3] + ~(*stand_alone);

    printf("0x%x\n", *final_result);
     
    return 0;
}

