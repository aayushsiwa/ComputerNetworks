// wap to extract each byte from a given number and store them in 
// separate character variables and print the content of those variables.

#include<stdio.h>

void main(){
    int num = 0x12345678;
    char byte1, byte2, byte3, byte4;

    byte1 = (num & 0xFF);
    byte2 = (num & 0xFF00) >> 8;
    byte3 = (num & 0xFF0000) >> 16;
    byte4 = (num & 0xFF000000) >> 24;

    printf("Byte1: %x\n", byte1);
    printf("Byte2: %x\n", byte2);
    printf("Byte3: %x\n", byte3);
    printf("Byte4: %x\n", byte4);
}