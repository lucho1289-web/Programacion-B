#include <stdio.h>
#define max 100

void duplica(int*,int);

int main()
{ int v[max]={0},N,i;
    printf("Cant de elementos \n");
    scanf("%d",&N);
    for (i=0;i<N;i++)
    { printf("Ingrese elemento \n");
    scanf("%d",&v[i]);
    }
    duplica(v,N);
    return 0;
}
void duplica(int *v,int N)
{
    int i;
    for(i=1;i<N;i++)
            if (i%2!=0)
        v[i]*=2;
}
