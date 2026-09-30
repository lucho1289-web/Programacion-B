#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct nodol
{
    char letra;
    struct nodol *ant, *sig;
}nodol;

typedef struct tldoble
{
    struct nodol *pri,*ult;
}tldoble;


void cargalista(tldoble *listaletra);
void muestralista(tldoble listaletra);
int esvocal(char letra);
int cantvocales(tldoble listaletra);
void elimina(tldoble *listaletra, int p);

void cargalista(tldoble *listaletra)
{
    char resp;
    nodol *nuevo;

    /* Inicializamos la lista vacía */
    listaletra->pri = NULL;
    listaletra->ult = NULL;

    printf("¿Desea ingresar una letra? (s/n): ");
    scanf(" %c", &resp);

    while (resp == 's' || resp == 'S')
    {
        /* Creamos el nodo */
        nuevo = (nodol *)malloc(sizeof(nodol));
        printf("Ingrese la letra: ");
        scanf(" %c", &nuevo->letra);

        nuevo->sig = NULL;

        /* Enlace de la lista doble */
        if (listaletra->pri == NULL)
        {
            /* Caso 1: La lista estaba vacía */
            nuevo->ant = NULL;
            listaletra->pri = nuevo;
            listaletra->ult = nuevo;
        }
        else
        {
            /* Caso 2: Inserción al final usando el puntero ult */
            nuevo->ant = listaletra->ult;
            listaletra->ult->sig = nuevo;
            listaletra->ult = nuevo;
        }

        printf("¿Desea ingresar otra letra? (s/n): ");
        scanf(" %c", &resp);
    }
}
void muestralista(tldoble listaletra)
{
    nodol *act=listaletra.pri;

        while (act!=NULL)
        {
            printf("%c \n",act->letra);
            act=act->sig;
        }
}

int esvocal(char letra)
{
    if(toupper(letra)=='A'||toupper(letra)=='E'||toupper(letra)=='I'||toupper(letra)=='O'||toupper(letra)=='U')
    return(1);
    else
        return(0);
}

int cantvocales(tldoble listaletra)
{ int cant=0;
  nodol *act=listaletra.pri;

    while(act!=NULL)
    {
        if (esvocal(act->letra))
            ++cant;
        act=act->sig;
    }
    return(cant);

}

void elimina(tldoble *listaletra, int  p)
{ nodol *act=listaletra->pri,*elim;
int i=1;

    while (act!=NULL && i<p)
        {
         act=act->sig;
         ++i;
        }

    if (act!=NULL)
    {
        elim=act;
        if (act->ant==NULL)
        {
            if (act->sig==NULL)
            {
                listaletra->pri=NULL;
                listaletra->ult=NULL;
            }
            else
            {
                listaletra->pri=act->sig;
                act->sig->ant=NULL;
            }
        }
        else
        {
            if(act->sig==NULL)
            {
                listaletra->ult=act->ant;
                act->ant->sig=NULL;
            }
            else
            {
                act->ant->sig=act->sig;
                act->sig->ant=act->ant;
            }
        }
        free(elim);
    }
    else
        printf("lista vacia\n");

}

int main()
{ tldoble listaletra;
  int p,x;
     printf("ingrese posicion \n ");
     scanf("%d",&p);
     cargalista(&listaletra);
     muestralista(listaletra);
      x=cantvocales(listaletra);
     printf("%d",x);
     elimina(&listaletra, p);
     return(0);
}
