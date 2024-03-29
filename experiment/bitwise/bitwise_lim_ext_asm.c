/*Bitwise custom program*/
//Compute different bitwise logic operations on a user-defined vector 

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{    

    int N = 5, i;
    int sum_a = 0xFFFFFFFF, sum_b = 0xFFFFFFFF;
    volatile int (*vector);
    volatile int (*stand_alone);
    volatile int (*final_result);

    register unsigned int x0 asm("x0");
	
    //define variables' addresses
    // vector = (volatile int(*)[N]) 0x030000, 
    // stand_alone = (volatile int(*))0x30040, 
    // final_result= (volatile int(*))0x30044;
    vector = (volatile int(*))malloc(N * sizeof(int));
    stand_alone = (volatile int(*))malloc(sizeof(int));
    final_result = (volatile int(*))malloc(sizeof(int));

    //configuration address, where the config of the memory is stored.
    int cnfAddress = 0x1fffc;
	// //configure vector[N-1] address
	// int andAddress = 0x030010;
	// //configure vector[N-2] address
	// int xorAddress  = 0x03000C;
    // //configure vector[N-3] address
	// int opAddress  = 0x30008;


    //initialize mask values
    int mask_and  = 0x8F;
    int mask_or   = 0xF1;
    int mask_xor  = 0xF0;
   	
	
    /* fill vector */
    for(i=0; i<N; i++){    
    	*(vector+i) = i*13467;
    }

    (*stand_alone) = *(vector + 1)+0x768;
	

    /* OR operation */
    //program LiM for range operation
    asm volatile("sw_active_or %[result], %[input_i], 0"
    :
    : [input_i] "r" (cnfAddress), [result] "r" (N)
    );
    //pointer of vector 0x20010
    //pointer of mask_or 0x7ffffffffffffed8

    //sw operation to active OR LiM
    // *(vector) = mask_or;
    asm volatile("sw %[data], 0(%[address])"
    : 
    : [data] "r" (mask_or), [address] "r" (vector)
    );

    //program LiM for stand-alone operation
    asm volatile("sw_active_or %[result], %[input_i], 0"
    :
    : [input_i] "r" (cnfAddress), [result] "r" (x0)
    );

	(*stand_alone) = mask_or;
    asm volatile("sw %[data], 0(%[address])"
    : 
    : [data] "r" (mask_or), [address] "r" (stand_alone)
    );
    printf("0x%x\n", *stand_alone);

    /* AND operation */

    //program LiM for stand-alone operation
    asm volatile("sw_active_and %[result], %[input_i], 0"
    :
    : [input_i] "r" (cnfAddress), [result] "r" (x0)
    );
	

    //lw_mask operation for mask_and computation
    // asm volatile("lw_mask %[result], %[input_s], %[input_t], 0 "
    // : [result] "=r" (mask_and)
    // : [input_s] "r" (andAddress), [input_t] "r"  (mask_and), "[result]" (mask_and)
    // );
    // mask_and = *(vector + N - 1);
    asm volatile("sw %[data], 0(%[address])"
    : 
    : [data] "r" (*(vector + N - 1)), [address] "r" (&mask_and)
    );
    printf("mask_and = 0x%x\n", mask_and);

    //program LiM for range operation
    asm volatile("sw_active_and %[result], %[input_i], 0"
    : 
    : [input_i] "r" (cnfAddress), [result] "r" (N)
    );

    //sw operation to active AND LiM
    // *(vector) = mask_and;
    asm volatile("sw %[data], 0(%[address])"
    : 
    : [data] "r" (mask_and), [address] "r" (vector)
    );

    //program LiM for stand-alone operation
    asm volatile("sw_active_and %[result], %[input_i], 0"
    : 
    : [input_i] "r" (cnfAddress), [result] "r" (x0)
    );

	// (*stand_alone) = mask_and;
    asm volatile("sw %[data], 0(%[address])"
    : 
    : [data] "r" (mask_and), [address] "r" (stand_alone)
    );
    printf("0x%x\n", *stand_alone);


    /* XOR operation*/

    //program LiM for stand-alone operation
    asm volatile("sw_active_xor %[result], %[input_i], 0"
    : 
    : [input_i] "r" (cnfAddress), [result] "r" (x0)
    );


    //lw_mask operation for mask_xor computation
    // asm volatile("lw_mask %[result], %[input_s], %[input_t], 0 "
    // : [result] "=r" (mask_xor)
    // : [input_s] "r" (xorAddress), [input_t] "r"  (mask_xor), "[result]" (mask_xor)
    // );
    //mask_xor = *(vector + N - 2);
    asm volatile("sw %[data], 0(%[address])"
    : 
    : [data] "r" (*(vector + N - 2)), [address] "r" (&mask_xor)
    );
    printf("mask_xor = 0x%x\n", mask_xor);


    //program LiM for range operation
    asm volatile("sw_active_xor %[result], %[input_i], 0"
    :
    : [input_i] "r" (cnfAddress), [result] "r" (N)
    );

    //*(vector) = mask_xor;
    asm volatile("sw %[data], 0(%[address])"
    : 
    : [data] "r" (mask_xor), [address] "r" (vector)
    );

    //program LiM for stand-alone operation
    asm volatile("sw_active_xor %[result], %[input_i], 0"
    : 
    : [input_i] "r" (cnfAddress), [result] "r" (x0)
    );

    // (*stand_alone) = mask_xor;
    asm volatile("sw %[data], 0(%[address])"
    : 
    : [data] "r" (mask_xor), [address] "r" (stand_alone)
    );

    printf("0x%x\n", *stand_alone);

    //lw_mask operation for ~(*vector)[N-3] computation exploting xor
    // asm volatile("lw_mask %[result], %[input_s], %[input_t], 0 "
    // : [result] "=r" (sum_a)
    // : [input_s] "r" (opAddress), [input_t] "r"  (sum_a), "[result]" (sum_a)
    // );
    // sum_a = *(vector + N - 3);
    asm volatile("sw %[data], 0(%[address])"
    : 
    : [data] "r" (*(vector + N - 3)), [address] "r" (&sum_a)
    );


    //lw_mask operation for ~(*stand_alone) computation exploting xor
    // asm volatile("lw_mask %[result], %[input_s], %[input_t], 0 "
    // : [result] "=r" (sum_b)
    // : [input_s] "r" (&(*stand_alone)), [input_t] "r"  (sum_b), "[result]" (sum_b)
    // );
    // sum_b = *(stand_alone);
    asm volatile("sw %[data], 0(%[address])"
    : 
    : [data] "r" (*(stand_alone)), [address] "r" (&sum_b)
    );



    //restore standard operations
    asm volatile("sw_active_none %[result], %[input_i], 0"
    : 
    : [input_i] "r" (cnfAddress), [result] "r" (x0)
    );

    (*final_result) = sum_a + sum_b;

    printf("0x%x\n", *final_result);

    return 0;
}
