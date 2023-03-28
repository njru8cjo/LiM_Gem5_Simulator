/*Max-Min research program*/
//Search max and min values in a user-defined vector of 10 elements

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{    
    /* variable declaration */
    int N = 10;
    int i;
    volatile int (*vector);

    register unsigned int x0 asm("x0");

    //define variable addresses
    vector = (volatile int(*))malloc(N * sizeof(int));
    int max, min;
    max = 0xffff2;
    int *temp = (int(*))malloc(sizeof(int));

    //configuration address, where the config of the memory is stored.
    int cnfAddress = 0x1fffc;
    
    /* fill vector */
    for(i=0; i<N; i++){    
    	vector[i] = 0x9c9c9c9c9c9c9c;
    }

    for(int i = 0; i < N; i++)
    {
        printf("vector[%d] x= %08x, d=%d, p = %p\n", i, vector[i], vector[i], &vector[i]);
    }
    

    // int *kkk = (int *)malloc(sizeof(int));
    // *kkk = 0x20010;
    // __uint8_t *p2 = (__uint8_t *)kkk;
    // printf("p2[0] = %02x\n", p2[0]);
    // printf("p2[1] = %02x\n", p2[1]);
    // printf("p2[2] = %02x\n", p2[2]);
    // printf("p2[3] = %02x\n", p2[3]);

    __uint8_t *p1 = (int *)malloc(sizeof(__uint8_t) * 4);
    *(int *)(p1) = 0x20010;
    printf("p1[0] = %02x\n", p1[0]);
    printf("p1[1] = %02x\n", p1[1]);
    printf("p1[2] = %02x\n", p1[2]);
    printf("p1[3] = %02x\n", p1[3]);

    int *p_data = (int *)p1;

    // *getConstPtr = (int *)p1;
    // printf("*(getConstPtr) = %d, p = %p\n", *(getConstPtr), *(getConstPtr));
    // printf("*((int *)*(getConstPtr) = %d\n", *((int *)*(getConstPtr)));
    
    // printf("aaa = %d\n",*( ((int *)(0x20018))));

    for(int i = 0; i < N; i++)
    {
       printf("*((int *)*(p_data+%d) = %d\n", i, *( ((int *)*(p_data)) + i ));
    }
       
    printf("\n");
    printf("pointer of min = %p\n", &min);
    printf("pointer of max = %p\n", &max);
    printf("=======================================\n");

    vector[0] = 0x224;
    //program LiM for max operation
    asm volatile("sw_active_max %[result], %[input_i], 0"
    : 
    : [input_i] "r" (cnfAddress), [result] "r" (N)
    );

    // /* MAX operation */

    // //use sw to active sw_max (max searched in all vector elements)
    // // max = vector;
    asm volatile("sw %[data], 0(%[address])"
    : 
    : [data] "r" (vector), [address] "r" (temp)
    );

    //program LiM for min operation
    asm volatile("sw_active_min %[result], %[input_i], 0"
    :
    : [input_i] "r" (cnfAddress), [result] "r" (N)
    );

    // /* MIN operation */
    // //use sw to active sw_min (min searched in all vector elements)
    // min = vector[0];
    asm volatile("sw %[data], 0(%[address])"
    : 
    : [data]"r" (vector), [address] "r" (&min)
    );


    //restore standard operations
    asm volatile("sw_active_none %[result], %[input_i], 0"
    :
    : [input_i] "r" (cnfAddress), [result] "r" (x0)
    );

    for(int i = 0; i < N; i++)
    {
        printf("vector[%d] x= %08x, d=%d\n", i, vector[i], vector[i]);
    }

    printf("max : %d , x = %08x\n", max, max);
    printf("min : %d , x = %08x\n", min, min);

    return EXIT_SUCCESS;
}

