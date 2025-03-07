// wap to enter a number and store the number across the following structure and print the content of the structure.

#include <stdio.h>

struct pkt
{
    char ch1;
    char ch2[2];
    char ch3;
};

void main()
{
    struct pkt p;
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    p.ch1 = (num & 0xFF);
    p.ch2[0] = (num & 0xFF00) >> 8;
    p.ch2[1] = (num & 0xFF0000) >> 16;
    p.ch3 = (num & 0xFF000000) >> 24;

    printf("ch1: %x\n", p.ch1);
    printf("ch2: %x\n", p.ch2[0]);
    printf("ch3: %x\n", p.ch2[1]);
    printf("ch4: %x\n", p.ch3);
}