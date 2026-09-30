#include <stdio.h>
#include <stdlib.h>

typedef struct nodocar{
    char letra;
    struct nodocar *ant, *sig;
} nodocar;

typedef struct TListad{
    struct nodocar *pri, *ult;
} TListad;

void cargalista(TListad *listacaracter);
int espalindroma(TListad listacaracter);

void cargalista(TListad *listacaracter)
{
    char resp;
    nodocar *nuevo;

    printf("¿Desea ingresar una letra? (s/n): ");
    scanf(" %c", &resp);

    while (resp == 's' || resp == 'S')
    {
        nuevo = (nodocar *)malloc(sizeof(nodocar));
        printf("Ingrese la letra: ");
        scanf(" %c", &nuevo->letra);

        nuevo->sig = NULL;

        if (listacaracter->pri == NULL)
        {

            nuevo->ant = NULL;
            listacaracter->pri = nuevo;
            listacaracter->ult = nuevo;
        }
        else
        {

            nuevo->ant = listacaracter->ult;
            listacaracter->ult->sig = nuevo;
            listacaracter->ult = nuevo;
        }

        printf("¿Desea ingresar otra letra? (s/n): ");
        scanf(" %c", &resp);
    }
}

int espalindroma(TListad Listacaracter)
{   nodocar * p, * u ;
    if (Listacaracter.pri!=NULL && Listacaracter.ult!=NULL)
    {   p=Listacaracter.pri;
        u=Listacaracter.ult;

        while (p!=u && p->letra == u->letra&& p->sig!=u)
        { p=p->sig;
          u=u->ant;
        }


        return(p->letra==u->letra);
    }
    else
        return(0);

}

int main()
{
    TListad lista_palabra;


    lista_palabra.pri = NULL;
    lista_palabra.ult = NULL;

    printf("--- CARGA DE LA PALABRA ---\n");
    cargalista(&lista_palabra);


    if (lista_palabra.pri != NULL)
    {
        if (espalindroma(lista_palabra) == 1)
            printf("\nLa palabra ES palindroma.\n");
        else
            printf("\nLa palabra NO ES palindroma.\n");
    }
    else
    {
        printf("\nLa lista esta vacia.\n");
    }

    return 0;
}
