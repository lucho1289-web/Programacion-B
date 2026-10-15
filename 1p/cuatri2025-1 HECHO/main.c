#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char st10[11], st15[16];

/* ==========================================
 *   INICIO TDA COLA Y TIPOS FALTANTES
 * ========================================== */
typedef struct {
    st15 codigoc;
    float cant;
} Telementoc;

typedef struct nodoc {
    Telementoc dato;
    struct nodoc *sig;
} nodoc;

typedef struct {
    nodoc *pri, *ult;
} Tcola;

void iniciac(Tcola *C) {
    C->pri = NULL;
    C->ult = NULL;
}

int vaciac(Tcola C) {
    return C.pri == NULL;
}

void ponec(Tcola *C, Telementoc X) {
    nodoc *aux = (nodoc *)malloc(sizeof(nodoc));
    aux->dato = X;
    aux->sig = NULL;
    if (C->pri == NULL)
        C->pri = aux;
    else
        C->ult->sig = aux;
    C->ult = aux;
}

void sacac(Tcola *C, Telementoc *X) {
    nodoc *aux;
    if (C->pri != NULL) {
        aux = C->pri;
        *X = aux->dato;
        C->pri = C->pri->sig;
        if (C->pri == NULL)
            C->ult = NULL;
        free(aux);
    }
}
/* ==========================================
 *   FIN TDA COLA
 * ========================================== */


typedef struct nodosub {
    st10 fecha;
    float precioc;
    int cantidadc;
    struct nodosub *sig; } nodosub;

typedef struct nodosub *Tsub;

typedef struct nodolista {
    st15 codigols;
    float preciov, margen, stockls;
    Tsub sub;
    struct nodolista *sig; } nodolista;

typedef struct nodolista *TLsimple;

typedef struct nodod {
    struct nodod *ant, *sig;
    st15 codigold;
    float stockld; } nodod;

typedef struct nodod *pnodod;

typedef struct TLdoble {
    pnodod pri, ult; } TLdoble;

void muestra_LD(TLdoble LD);
void muestra_LS(TLsimple LS);
void cargacola ( Tcola *C);
void cargalista( TLsimple *LS);

void agregald( TLdoble *LD, st15 codigo, float unidades);

void procesacompra( Tcola *C, TLsimple *LS, TLdoble *LD);

void eliminald( TLdoble *LD, st15 codigo);


void compraproveedor( TLdoble *LD , TLsimple *LS);

/* ==========================================
 *   INICIO MOCKS DE CARGA AUTOMATICA
 * ========================================== */
void cargacola( Tcola *C)
{
    Telementoc e1, e2;

    strcpy(e1.codigoc, "A123");
    e1.cant = 15.0; // Provocará que el stock de A123 quede negativo (-5)
    ponec(C, e1);

    strcpy(e2.codigoc, "B456");
    e2.cant = 2.0;  // El stock de B456 quedará positivo (18)
    ponec(C, e2);

    printf(">>> Cola de compras cargada automaticamente <<<\n");
}

void cargalista( TLsimple *LS)
{
    TLsimple n1 = (TLsimple)malloc(sizeof(nodolista));
    strcpy(n1->codigols, "A123");
    n1->preciov = 150.0;
    n1->margen = 20.0;
    n1->stockls = 10.0;
    n1->sub = NULL;

    TLsimple n2 = (TLsimple)malloc(sizeof(nodolista));
    strcpy(n2->codigols, "B456");
    n2->preciov = 300.0;
    n2->margen = 15.0;
    n2->stockls = 20.0;
    n2->sub = NULL;

    n1->sig = n2;
    n2->sig = NULL;

    *LS = n1;
    printf(">>> Lista TLsimple cargada automaticamente <<<\n\n");
}
/* ==========================================
 *   FIN MOCKS DE CARGA AUTOMATICA
 * ========================================== */


void agregald( TLdoble *LD, st15 codigo, float unidades)
{  pnodod nuevo=(pnodod) malloc(sizeof(nodod));
   strcpy(nuevo->codigold, codigo);

   nuevo->stockld = unidades; nuevo->ant=NULL;
   nuevo->sig=NULL;
   if ( LD->pri==NULL)
       LD->pri=nuevo;

   else
   { nuevo->ant = LD->ult;
     LD->ult->sig = nuevo;
   }

   LD->ult=nuevo;
}

void muestra_LD(TLdoble LD) {
    pnodod act = LD.pri;
    printf("\n--- LISTA DOBLE (Productos Faltantes) ---\n");
    if (act == NULL) {
        printf("Vacia.\n");
    }
    while (act != NULL) {
        printf("Codigo: %s | Stock faltante: %.2f\n", act->codigold, act->stockld);
        act = act->sig;
    }
}

void muestra_LS(TLsimple LS) {
    TLsimple act = LS;
    Tsub auxsub;
    printf("\n--- LISTA SIMPLE (Stock Actualizado y Sublista de Compras) ---\n");
    if (act == NULL) {
        printf("Vacia.\n");
    }
    while (act != NULL) {
        printf("Producto: %s | Stock actual: %.2f | Precio Vta: %.2f\n", act->codigols, act->stockls, act->preciov);
        auxsub = act->sub;
        if (auxsub == NULL) {
            printf("   -> [Sin ingresos de proveedores]\n");
        }
        while (auxsub != NULL) {
            printf("   -> Proveedor - Fecha: %s | Cant: %d | Precio Compra: %.2f\n", auxsub->fecha, auxsub->cantidadc, auxsub->precioc);
            auxsub = auxsub->sig;
        }
        act = act->sig;
    }
}
void procesacompra( Tcola *C , TLsimple *LS, TLdoble *LD)
{   TLsimple aux;
    float acumimporte=0;
    int cant =0;
    Telementoc reg;


    while (!vaciac(*C))
    {   sacac (C, &reg);
        aux = *LS;

        while ( strcmp(aux->codigols, reg.codigoc) !=0)
            aux=aux->sig;
        aux->stockls -= reg.cant;
        if (aux->stockls <0)
            agregald( LD, aux->codigols, aux->stockls);
        acumimporte += aux->preciov;
        ++cant;
    }

    printf("importe total %f \n importe promedio por producto %f \n", acumimporte,acumimporte/cant );

}


void eliminald( TLdoble *LD, st15 codigoa)
{  pnodod act = LD->pri, elim;

    while( act!= NULL )
    {   if ( strcmp(act->codigold, codigoa)==0)
        {
            elim=act;

            if (act == LD->pri)
            { if (act == LD->ult)
                { LD->pri= NULL;
                  LD->ult=NULL;
                }
              else
              { act=act->sig;
                act->ant=NULL;
                LD->pri=act;
              }
            }
            else
            { if ( act== LD->ult)
                {
                elim->ant->sig=NULL;
                LD->ult = elim->ant;
                }
              else
                { act = act->sig;
                  act->ant = elim->ant;
                  elim->ant->sig=act;
                }
            }
            free(elim);
        }
    act=act->sig;}

    }



void compraproveedor(TLdoble *LD, TLsimple *LS)
{
    FILE *proveen;
    TLsimple ant = NULL, act, nuevo;
    st15 codigoa;
    Tsub nuevos = (Tsub)malloc(sizeof(nodosub));

    proveen = fopen("PROVEEN.txt", "rt");

    while (fscanf(proveen, "%s %s %d %f", nuevos->fecha, codigoa, &(nuevos->cantidadc), &(nuevos->precioc)) == 4)
    {
        if (nuevos->fecha[2] == '2' && nuevos->fecha[3] == '5' && nuevos->fecha[6] == '4')
        {   ant=NULL;
            act = *LS;

            while (act != NULL && strcmp(act->codigols, codigoa) < 0)
            {
                ant = act;
                act = act->sig;
            }

            if (act == NULL || strcmp(act->codigols, codigoa) != 0)
            {
                nuevo = (TLsimple)malloc(sizeof(nodolista));
                strcpy(nuevo->codigols, codigoa);
                nuevo->stockls = nuevos->cantidadc;
                nuevo->margen = 50;
                nuevo->preciov = (1.5 * nuevos->precioc);
                nuevo->sub = NULL;

                if (ant == NULL)
                {
                    nuevo->sig = *LS;
                    *LS = nuevo;
                }
                else
                {
                    ant->sig = nuevo;
                    nuevo->sig = act;
                }

                act = nuevo;
            }
            else
            {
                act->preciov = (nuevos->precioc * act->margen);

                /* Evaluamos la condicion con el stock viejo ANTES de sumarlo */
                if (act->stockls < 0 && (act->stockls + nuevos->cantidadc) > 0)
                {
                    eliminald(LD, codigoa);
                }

                /* Ahora si, actualizamos la variable */
                act->stockls += nuevos->cantidadc;
            }

            nuevos->sig = act->sub;
            act->sub = nuevos;

            nuevos = (Tsub)malloc(sizeof(nodosub));
        }
    }

    free(nuevos); /* Destruimos la ultima caja no utilizada */
    fclose(proveen);
}




int main(){

  TLdoble LD ;
  TLsimple LS = NULL;
  Tcola C  ;

    LD.pri= NULL;
    LD.ult= NULL;
    iniciac(&C);
    cargacola( &C);
    cargalista( &LS) ;
    procesacompra( &C, &LS, &LD);

    compraproveedor(&LD, &LS);

    /* Agregamos las muestras acá */
    muestra_LS(LS);
    muestra_LD(LD);

    return(0);

}
