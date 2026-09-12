#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char st8[8];
typedef struct nodocyp
{
    int cant;
    st8 pal;
    struct nodocyp *sig;
}nodocyp;
typedef struct nodocyp *tlista;

void generalista(tlista *palabras);
void muestralista(tlista palabras);

void generalista(tlista *palabras)
{
    FILE *texto;
    st8 elemen;
    tlista ant,act,nuevo;

    texto=fopen("texto.txt","rt");

    while (fscanf(texto,"%s",elemen)==1)
    {
        ant=NULL;
        act=*palabras;
        while(act!=NULL && strcmp(act->pal,elemen)<0)
        {
            ant=act;
            act=act->sig;
        }

            if (act==NULL||strcmp(act->pal,elemen)>0)
                 {
                    nuevo=(tlista)malloc(sizeof(nodocyp));
                    strcpy(nuevo->pal,elemen);
                    nuevo->cant=1;

                    if (ant==NULL)
                    {
                      nuevo->sig=*palabras;
                      *palabras=nuevo;

                    }
                    else
                    {
                        ant->sig=nuevo;
                        nuevo->sig=act;
                    }


                 }
            else
                (act->cant)+=1;
    }

    fclose(texto);
}
void muestralista(tlista palabras)
{
    tlista act;
    act=palabras;

    while (act!=NULL)
    {
        printf("%s, %d",act->pal,act->cant);
        act=act->sig;
    }

}
int main()
{ tlista palabras=NULL;

    generalista(&palabras);
    muestralista(palabras);

    return 0;
}
