#include <stdio.h>
#include <stdlib.h>

typedef struct nodod {
    struct nodod *sig, *ant;
    char letra;}nodod;

typedef nodod *pnodod;

typedef struct TLista{
    pnodod pri,ult;}TLista;

void cargalista(TLista *Ldoble , pnodod *anterior);
void muestralista(TLista Ldoble);
int cuenta( pnodod act );
void insertomedio(TLista *Ldoble);
void elimina (TLista *Ldoble, pnodod anterior);

void eliminax( TLista *Ldoble, char x);

/* Subprograma de carga automática (Mock) */
void cargalista(TLista *Ldoble, pnodod *anterior) {
    pnodod n1, n2, n3, n4;

    /* 1. Reservamos memoria para 4 nodos de prueba */
    n1 = (pnodod)malloc(sizeof(nodod));
    n2 = (pnodod)malloc(sizeof(nodod));
    n3 = (pnodod)malloc(sizeof(nodod));
    n4 = (pnodod)malloc(sizeof(nodod));

    /* 2. Asignamos los datos (letras) */
    n1->letra = 'A';
    n2->letra = 'B';
    n3->letra = 'C';
    n4->letra = 'D';

    /* 3. Enlazamos los nodos doblemente: NULL <- A <-> B <-> C <-> D -> NULL */
    n1->ant = NULL;
    n1->sig = n2;

    n2->ant = n1;
    n2->sig = n3;

    n3->ant = n2;
    n3->sig = n4;

    n4->ant = n3;
    n4->sig = NULL;

    /* 4. Enganchamos la lista al TLista principal */
    Ldoble->pri = n1;
    Ldoble->ult = n4;

    /*
     * 5. Seteamos el puntero 'anterior'.
     * Si lo dejamos apuntando a n2 (letra 'B'), tu función 'elimina'
     * luego buscará eliminar el nodo siguiente a este (la 'C').
     */
    *anterior = n2;

    printf(">>> Lista cargada automaticamente: A, B, C, D <<<\n\n");
}


/* Subprograma para ir viendo qué pasa con la lista */
void muestralista(TLista Ldoble) {
    pnodod act = Ldoble.pri;

    if (act == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }

    printf("Estado de la lista: NULL <- ");
    while (act != NULL) {
        printf("[%c]", act->letra);
        if (act->sig != NULL) {
            printf(" <-> ");
        }
        act = act->sig;
    }
    printf(" -> NULL\n\n");
}
int cuenta(pnodod act )
{ int cont=0;

    while (act !=NULL)
    { ++cont;
        act = act ->sig;
    }
    return(cont);
}


void insertomedio(TLista *Ldoble)
{ pnodod nuevo=(pnodod) malloc(sizeof(nodod)) , act ;
    int x=0 , i=1;
    nuevo->letra='c';
    if ( Ldoble->pri !=NULL)
    { act=Ldoble->pri;
        x= cuenta( act );

        if ( x%2 == 0)

            x=x/2;
        else
            x=(x+1)/2;

        while (act!=NULL && i<= x)
            { act=act->sig;
                ++i ;
            }




        act->ant->sig = nuevo;
        nuevo->ant = act->ant;
        nuevo->sig=act;
        act->ant=nuevo;

    }
    else
    { Ldoble->pri=nuevo;
        Ldoble->ult=nuevo;
    }
}


void elimina(TLista *Ldoble, pnodod anterior)
{ pnodod act = Ldoble->pri;

    if (anterior==NULL)
    {
        if (Ldoble->pri == Ldoble->ult)
            Ldoble->pri= Ldoble->ult=NULL;
        else
        {
            Ldoble->pri = Ldoble->pri->sig;
            Ldoble->pri->ant=NULL;
        }

    }
    else
    {
        while (act->ant!=anterior)
            act=act->sig;

        if (act== Ldoble->ult)
        { anterior->sig = NULL;
            Ldoble->ult = anterior;
        }
        else
        { anterior->sig=act->sig;
          act->sig->ant=anterior;
        }
    }
    free(act);
}


void eliminax(TLista *Ldoble, char x )
{ pnodod act = Ldoble->pri , elim;

    while (act!= NULL )
    {   if (act->letra == x)
        { elim=act; act=act->sig;
            if (elim == Ldoble->pri)
            {
                if (elim == Ldoble->ult)
                { Ldoble->pri=NULL;
                    Ldoble->ult=NULL;
                }
                else
                {
                    Ldoble->pri= Ldoble->pri->sig;
                    Ldoble->pri->ant=NULL;
                }

            }
            else
            { if (elim == Ldoble->ult)
                    {
                       Ldoble->ult = Ldoble->ult->ant;
                       Ldoble->ult->sig=NULL;
                    }


                else
                { elim->ant->sig=act;
                    act->ant = elim->ant;
                }
            }

            free(elim);
        }
        else
            act=act->sig;
    }
}

int main()
{ TLista Ldoble ;
Ldoble.pri=NULL;
Ldoble.ult=NULL;
    pnodod anterior;
    char x;
    cargalista(&Ldoble, &anterior);
    muestralista(Ldoble);
    insertomedio(& Ldoble);

    muestralista(Ldoble);
    elimina (&Ldoble, anterior);

    muestralista(Ldoble);
    printf("ingrese elemento a eliminar \n");
    scanf(" %c", &x);

    eliminax( &Ldoble,x);

    muestralista(Ldoble);
    return(0);
}
