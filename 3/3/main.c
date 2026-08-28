//dado un vector A de N elementos, obtener el promedio de sus elementos
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int suma(int vectorej[],int N)
{
    if (N==0)
        return(0);
    else
        return(suma(vectorej,N-1)+vectorej[N-1]);
}


int main()
{ int vectorej[MAX],N;
  float prom;
    printf("Inserte cantidad de elementos del vector\n");
    scanf("%d",&N);
    cargavector(vectorej,N);
    prom=(float)suma(vectorej,N)/N;
    return 0;
}


