
#include <stdlib.h>
#include <stdio.h>
int* crea(int);
void ingresa(int,int*);

int main()
{
    int N,*v=NULL;
    printf("Cant de elementos del vector");
    scanf("%d",&N);
    v=crea(N);
    ingresa(N,v);
    return 0;
}
int *crea(int N)
{ int *p;

    p=(int*)malloc(N*sizeof(int));
    return(p);
}
void ingresa(int N,int *v)
{int i;
for(i=0;i<N;i++)
{printf("ingrese elemento");
scanf("%d",v+i);
}

}


