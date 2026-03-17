#include <stdio.h>

int consecutivos(int,int,int);
int main()
{
    int a,b,c,d;


    printf("Ingrese tres numeros");
    scanf("%d %d %d",&a,&b,&c);
    d=consecutivos(a,b,c);
    if (d==1)
        printf("Son consecutivos");
    else
        printf("No son consecutivos");

    return 0;
}
int consecutivos(int a, int b, int c)
{
    if ((a==b+1 && b==c+1)||(a==b-1 && b==c-1))
        return 1;
    else
        return 0;
}
