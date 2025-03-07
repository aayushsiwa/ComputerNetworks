// wap to check whether the machine is in little endian or big endian.
// enter a number, print the content of each byte location and convert the endianess 
// of the number and print the content of each byte location.

#include<stdio.h>

void main(){
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Number: %d\n", num);
    printf("Byte 1: %d\n", (num & 0x000000FF));
    printf("Byte 2: %d\n", (num & 0x0000FF00) >> 8);
    printf("Byte 3: %d\n", (num & 0x00FF0000) >> 16);
    printf("Byte 4: %d\n", (num & 0xFF000000) >> 24);
    printf("Number in little endian: %d\n", ((num & 0x000000FF) << 24) | ((num & 0x0000FF00) << 8) | ((num & 0x00FF0000) >> 8) | ((num & 0xFF000000) >> 24));
}