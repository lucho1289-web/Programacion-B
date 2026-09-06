#include <stdio.h>
#include <stdlib.h>
//dada una lista simplemente enlazada de caracteres, escribir una funcion void que//
//a.muestre su contenido b. devuelva la cantidad de nodos que poseen vocales  c.indique si la lista esta ordenada d.elimine el elemento ubicado en una posicion pasada como parametro//
typedef struct nodoletra
{
    char letra;
    struct nodoletra *sig;
}nodoletra;

typedef nodoletra *tlista;
void muestra(tlista);
int esvocal(char);
void vocales(tlista);
void orden(tlista);
void elimina(tlista*);

void muestra(tlista listaletra)
{
    tlista aux;
    if (listaletra!=NULL)
    {
        aux=listaletra;
        while(aux!=NULL)
        {
            printf("%c",aux->letra);
            aux=aux->sig;
        }
    }
    else
        printf("lista vacia");
}

int esvocal(char letra)
{
    return(letra=='a'||letra=='e'||letra=='i'||letra=='o'||letra=='u');
}
void vocales(tlista listaletra)
{
    tlista aux;
    int cant=0;

    if (listaletra!=NULL)
    {
        aux=listaletra;
        while(aux!=NULL)
        {
            if(esvocal(aux->letra))
                ++cant;
                aux=aux->sig;
        }
        printf("cant de vocales %d ",cant);

    }
    else
        printf("lista vacia");
}
void orden(tlista listaletra)
{
 int verifica=1;
 tlista ant,act;

 if(listaletra!=NULL)
 {
     act=listaletra->sig;
     ant=listaletra;
     while(act!=NULL && verifica)
     {
         if(ant->letra>act->letra)
            verifica=0;
         else
         {
             ant=act;
             act=act->sig;
         }
     }
     if (verifica)
        printf("lista ordenada");
     else
        printf("lista no ordenada");
 }
 else
    printf("lista vacia");
}

void elimina(tlista *listaletra,int posicion)
{
    tlista act,ant;
    int i=1;

    if(*listaletra!=NULL)
    {
        act=*listaletra;
        ant=NULL;
        while (act!=NULL && i<posicion)
        {
            ++i;
            ant=act;
            act=act->sig;
        }

        if (i==1)
         *listaletra=act->sig;
        else
        {
          if (act==NULL)
            printf("no existe esa posicion en la lista");
            else
            ant->sig=act->sig;
        }
        free(act);
    }
    else
       printf("lista vacia");
}
int main()
{   tlista listaletra;
    int posicion;
    listaletra=NULL;

    printf("ingrese posicion");
    scanf("%d",&posicion);
    muestra(listaletra);
    vocales(listaletra);
    orden(listaletra);
    elimina(&listaletra,posicion);

    return(0);

}
