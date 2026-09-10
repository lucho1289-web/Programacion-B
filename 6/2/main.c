#include <stdio.h>
#include <stdlib.h>
#define max 200

typedef struct nodoenteros
{
    int num;
    struct nodoenteros *sig;
}nodoenteros;

typedef nodoenteros *tlista;

void cargavector(int vecint[],int N);
void invertido(tlista *listaenteros,int vecint[],int N);
void mantiene(tlista *listamantiene,int vecint[],int N);
void insertaordenado(tlista *listaorden,int vecint[],int N);
void muestra(tlista lista);


void cargavector(int vecint[max],int N)
{
    int i;
    for (i=0;i<=N-1;i++)
    {
        printf("ingrese elemento");
        scanf("%d",&vecint[i]);
    }
}

void invertido(tlista *listaenteros,int vecint[],int N)
{
    int i;
    tlista nuevo;

    nuevo=(tlista) malloc(sizeof(nodoenteros));
    nuevo->num=vecint[0];
    nuevo->sig=NULL;
    *listaenteros=nuevo;

    for(i=1;i<=N-1;i++)
    {nuevo=(tlista) malloc(sizeof(nodoenteros));
     nuevo->num=vecint[i];
     nuevo->sig=*listaenteros;
     *listaenteros=nuevo;
    }
}

void mantiene (tlista *listamantiene,int vecint[],int N)
{   int i;
    tlista nuevo,act;

    nuevo=(tlista) malloc(sizeof(nodoenteros));
    nuevo->num=vecint[0];
    nuevo->sig=NULL;
    *listamantiene=nuevo;

    for(i=1;i<=N-1;i++)
    {act=nuevo;
     nuevo=(tlista) malloc(sizeof(nodoenteros));
     nuevo->num=vecint[i];
     nuevo->sig=NULL;
     act->sig=nuevo;
    }

}

void insertaordenado(tlista *listaorden,int vecint[],int N)
{
    int i;
    tlista ant,act,nuevo,aux;

    nuevo=(tlista) malloc(sizeof(nodoenteros));
    nuevo->num=vecint[0];
    nuevo->sig=NULL;
    *listaorden=nuevo;
    for(i=1;i<=N-1;i++)
    {
        nuevo=(tlista) malloc(sizeof(nodoenteros));
        nuevo->num=vecint[i];
        ant=NULL;
        act=*listaorden;

        while(act!=NULL && act->num<vecint[i])
        {
            ant=act;
            act=act->sig;
        }
        if(ant==NULL)
        {
            nuevo->sig=*listaorden;
            *listaorden=nuevo;
        }
        else
        {
            ant->sig=nuevo;
            nuevo->sig=act;
        }
    }

}

void muestra(tlista lista)
{tlista act;
    act=lista;
    while(act!=NULL)
    {
        printf("%d",act->num);
        act=act->sig;
    }

}

int main()
{
    tlista listainv,listaman,listainsord;
    int vecint[max],N;

    printf("ingrese numero de elementos del vector");
    scanf("%d",&N);
    cargavector(vecint,N);
    invertido(&listainv,vecint,N);
    mantiene(&listaman,vecint,N);
    insertaordenado(&listainsord,vecint,N);
    muestra(listainv);
    muestra(listaman);
    muestra(listainsord);


}
