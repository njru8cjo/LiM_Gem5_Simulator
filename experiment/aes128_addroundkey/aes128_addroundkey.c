#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    /* Others */
    int i, j;

    /* input variables declaration */
    int row = 4, col = 4;

    int* states[row];
    int* key[row];
    for (i = 0; i < row; i++)
        states[i] = (int*)malloc(col * sizeof(int));
    for (i = 0; i < row; i++)
        key[i] = (int*)malloc(col * sizeof(int));

    states[0][0]=0x32; states[0][1]=0x88; states[0][2]=0x31; states[0][3]=0xE0;
    states[1][0]=0x43; states[1][1]=0x54; states[1][2]=0x31; states[1][3]=0x37;
    states[2][0]=0xF6; states[2][1]=0x30; states[2][2]=0x98; states[2][3]=0x07;
    states[3][0]=0xA8; states[3][1]=0x8D; states[3][2]=0xA2; states[3][3]=0x34;

    key[0][0]=0x00; key[0][1]=0xA5; key[0][2]=0xA8; key[0][3]=0xA0;
    key[1][0]=0xE9; key[1][1]=0x09; key[1][2]=0xBB; key[1][3]=0x2A;
    key[2][0]=0xC9; key[2][1]=0xD4; key[2][2]=0xB7; key[2][3]=0xAB;
    key[3][0]=0xF2; key[3][1]=0xE8; key[3][2]=0x60; key[3][3]=0x08;



   /* Add around key */
   for (i=0; i<row; i++) {
       for (j=0; j<col; j++) {
           states[i][j] = states[i][j] ^ key[i][j];
           printf("%x ", states[i][j]);
       }
       printf("\n");
   }

   return EXIT_SUCCESS;
}

