/* Bitmap search program*/
//This program emulates the bitmap search algorithm, students' features are distributed over 6 integer vectors.
//In this program two queries are perfomed
// 1. Which students are male and older than 19?
// 2. Which students are older than 18?

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    /* variable declaration */
    int i, N=0; 
    int Nr = 6; //number of rows
    volatile int* result_M_over19;    //declare memory variables as volatile int
    volatile int* result_over18;
    volatile int* v_age16;
    volatile int* v_age17;
    volatile int* v_age18;
    volatile int* v_age19;
    volatile int* v_age20;
    volatile int* v_genderM;
    volatile int* v_genderF;

    register unsigned int x0 asm("x0");

    //configuration address, where the config of the memory is stored.
    int cnfAddress = 0x1fffc;
    
    //Define variable addresses
    result_M_over19 = (volatile int(*)) malloc(Nr * sizeof(int));
    result_over18   = (volatile int(*)) malloc(Nr * sizeof(int));
    v_age16         = (volatile int(*)) malloc(Nr * sizeof(int));
    v_age17         = (volatile int(*)) malloc(Nr * sizeof(int));
    v_age18         = (volatile int(*)) malloc(Nr * sizeof(int));
    v_age19         = (volatile int(*)) malloc(Nr * sizeof(int));
    v_age20         = (volatile int(*)) malloc(Nr * sizeof(int));
    v_genderM       = (volatile int(*)) malloc(Nr * sizeof(int));
    v_genderF       = (volatile int(*)) malloc(Nr * sizeof(int));
  
    /* Initialize bitmap */
    v_genderM[0]=0x00000000; v_genderM[1]=0x00000000; v_genderM[2]=0x00000000; v_genderM[3]=0xFFFFFFFF; v_genderM[4]=0xFFFFFFFF; v_genderM[5]=0xFFFFFFFF;
    v_genderF[0]=0xFFFFFFFF; v_genderF[1]=0xFFFFFFFF; v_genderF[2]=0xFFFFFFFF; v_genderF[3]=0x00000000; v_genderF[4]=0x00000000; v_genderF[5]=0x00000000;
    v_age16[0]  =0x00000000; v_age16[1]  =0x00000000; v_age16[2]  =0x0000FFFF; v_age16[3]  =0x00000000; v_age16[4]  =0x00000000; v_age16[5]  =0x0000FFFF;
    v_age17[0]  =0x00000000; v_age17[1]  =0x00000000; v_age17[2]  =0xFFFF0000; v_age17[3]  =0x00000000; v_age17[4]  =0x00000000; v_age17[5]  =0xFFFF0000;
    v_age18[0]  =0x00000000; v_age18[1]  =0x0000FFFF; v_age18[2]  =0x00000000; v_age18[3]  =0x00000000; v_age18[4]  =0x0000FFFF; v_age18[5]  =0x00000000;
    v_age19[0]  =0x00000000; v_age19[1]  =0xFFFF0000; v_age19[2]  =0x00000000; v_age19[3]  =0x00000000; v_age19[4]  =0xFFFF0000; v_age19[5]  =0x00000000;
    v_age20[0]  =0xFFFFFFFF; v_age20[1]  =0x00000000; v_age20[2]  =0x00000000; v_age20[3]  =0xFFFFFFFF; v_age20[4]  =0x00000000; v_age20[5]  =0x00000000;

    // Initialize results to 0 (useful for neutral lw_or operation)
    for(i=0; i<Nr; i++) {
        result_M_over19[i] = 0;
        result_over18[i]   = 0;
    }

    //program LiM for stand-alone OR operation
    // asm volatile("sw_active_or %[result], %[input_i], 0"
    // :
    // : [input_i] "r" (cnfAddress), [result] "r" (N)
    // );

    /* Query: identify male people that are 19 or 20 */
    for(i=0; i<Nr; i++) {
        int temp_a = 0, temp_b = 0;

        asm volatile("sw_active_or %[result], %[input_i], 0"
        :
        : [input_i] "r" (cnfAddress), [result] "r" (x0)
        );

        //load first operand with neutral load
        // asm volatile("lw_mask %[result], %[input_s], %[input_t], 0 "
        // : [result] "=r" (partial)
        // : [input_s] "r" (&v_age20[i]), [input_t] "r"  (x0), "[result]" (partial)
        // );
        temp_a = *(v_age20 + i);
        

        //lw_mask operation for OR computation, use previous operand as mask (equivalent to v_age19[i] | v_age20[i])
        // asm volatile("lw_mask %[result], %[input_s], %[input_t], 0 "
        // : [result] "=r" (partial)
        // : [input_s] "r" (&v_age19[i]), [input_t] "r"  (partial), "[result]" (partial)
        // );
        temp_a = *(v_age19 + i);

        //load last operand with neutral load
        // asm volatile("lw_mask %[result], %[input_s], %[input_t], 0 "
        // : [result] "=r" (operand)
        // : [input_s] "r" (&v_genderM[i]), [input_t] "r"  (x0), "[result]" (operand)
        // );
        temp_b = *(v_genderM + i);

        asm volatile("sw_active_none %[result], %[input_i], 0"
        : 
        : [input_i] "r" (cnfAddress), [result] "r"  (x0)
        );
        //sw operation to store results (neutral store)
        result_M_over19[i] = temp_a & temp_b;
    }

    /* Query: identify people that are older than 18 */
   for(i=0; i<Nr; i++) {

        int temp = 0;

        asm volatile("sw_active_or %[result], %[input_i], 0"
        :
        : [input_i] "r" (cnfAddress), [result] "r" (x0)
        );
        
        


        //lload first operand with neutral load
        // asm volatile("lw_mask %[result], %[input_s], %[input_t], 0 "
        // : [result] "=r" (partial)
        // : [input_s] "r" (&v_age17[i]), [input_t] "r"  (x0), "[result]" (partial)
        // );
        temp =  *(v_age17 + i);

        //lw_mask operation for OR computation, use previous operand as mask (equivalent to v_age17[i] | v_age16[i])
        // asm volatile("lw_mask %[result], %[input_s], %[input_t], 0 "
        // : [result] "=r" (partial)
        // : [input_s] "r" (&v_age16[i]), [input_t] "r"  (partial), "[result]" (partial)
        // );
        temp = *(v_age16 + i);

        asm volatile("sw_active_none %[result], %[input_i], 0"
        : 
        : [input_i] "r" (cnfAddress), [result] "r"  (x0)
        );
        
       //sw operation to store results (neutral store)
	   result_over18[i] = ~temp;
   }
 

    //restore standard operations
    // asm volatile("sw_active_none %[result], %[input_i], 0"
    // : 
    // : [input_i] "r" (cnfAddress), [result] "r"  (x0)
    // );

    /* print */

    for(i=0; i < Nr; i++) {
        printf("0x%x\n", result_M_over19[i]);
    }

    printf("===============================\n");

    for(i=0; i < Nr; i++) {
        printf("0x%x\n", result_over18[i]);
    }


    return EXIT_SUCCESS;
}

