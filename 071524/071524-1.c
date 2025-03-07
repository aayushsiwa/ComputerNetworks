// wap to swap two variables entered through cmd line using func and pointer

#include<stdio.h>

void main(){
    printf("Enter two variables a and b:\n");
    int a,b;
    scanf("%d %d",&a,&b);
    printf("Initially a is %d and b is %d\n",a,b);
    int *p;
    *p=a;
    a=b;
    b=*p;
    printf("Now a is %d and b is %d",a,b);
}