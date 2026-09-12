#include <stdio.h>
#include <stdlib.h>
#include "pilas.h"
#include "colas.h"

typedef struct nodo
{ tcola centeros;
  struct nodo *sig;
}nodol;

typedef struct nodol *tlista;
void generapila(tlista *listacolas,tpila *pilamax);
void generapila(tlista *listacolas,tpila *pilamax)
{
    tlista act;
    int elemen,max;

    act=*listacolas;
    while(act!=NULL)
    {   if (!vaciac(act->centeros))
        {
          sacac(&(act->centeros),&max);
        }
        while(!vaciac(act->centeros))
        {
            sacac(&(act->centeros),&elemen);
            if(elemen>max)
                max=elemen;
        }
        ponep(pilamax,max);
        act=act->sig;
    }


}
int main()
{ tpila pilamax;
  tlista listacolas=NULL;
  iniciap(&pilamax);
  generapila(&listacolas,&pilamax);
return 0;
}
