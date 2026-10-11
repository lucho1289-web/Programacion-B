#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 5
/* ==========================================
 *   INICIO TDA COLA Y TIPO TELEMENTOC
 * ========================================== */
 typedef char st8[9];
typedef struct {
    st8 documento;
    st8 d; /* Aislado para coincidir con tu llamado reg.d */
    char htipo;
    char habind;
    char ingcli;
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


typedef struct Tvecreg {
    char tipo;
    int canti;
} Tvecreg;

typedef struct nodosub {
    unsigned int numeroc;
    st8 dni;
    struct nodosub *sig;
} nodosub;

typedef struct nodosub *Tsublista;

typedef struct nodol {
    unsigned int numeroh;
    char tipoh;
    Tsublista subcamas;
    struct nodol *sig;
} nodol;

typedef struct nodol *TLsimple;

typedef struct nodod {
    struct nodod *ant, *sig;
    st8 doc;
    char htipo, indhab, cling;
} nodod;

typedef struct nodod *pnodod;

typedef struct TLdoble {
    pnodod pri, ult;
} TLdoble;


/* ==========================================
 *   PROTOTIPOS
 * ========================================== */

void cargavec(Tvecreg vectipos[ ]);
void cargaLD( TLdoble *LDP );
void cargaC( Tcola *C );
void cargaLH( TLsimple *LH );

void nohi( TLsimple *LH , Tsublista *auxsub, Telementoc reg);
void eshi( TLsimple *LH , Tsublista *auxsub, Telementoc reg);
void insertaLDP( TLdoble *LDP, Telementoc reg) ;
void eliminaLH( TLsimple *LH, st8 documento, Tsublista auxs);
void procesapedidos( TLsimple *LH, TLdoble *LDP, Tcola *C);
void incrementavec( Tvecreg vectipos[MAX], char tipo);
void eliminahabitaciones( Tvecreg vectipos[MAX], TLsimple *LH,
TLdoble *LDP);

void tipomax( Tvecreg vectipos[MAX], int i, int max, char *tipo);


/* ==========================================
 *   IMPLEMENTACIONES
 * ========================================== */
/* ==========================================
 *   FUNCIONES DE CARGA (Mocks)
 * ========================================== */
void cargavec(Tvecreg vectipos[]) {
    int i;
    for(i = 0; i < MAX; i++) {
        vectipos[i].tipo = 'A' + i; /* Genera tipos A, B, C... */
        vectipos[i].canti = 0;
    }
}

void cargaLD(TLdoble *LDP) {
    LDP->pri = NULL;
    LDP->ult = NULL;
    // La dejamos vacía a propósito para que veas cómo se llena
    // con los pacientes que se trasladan y los pedidos nuevos.
}
Tsublista nuevaCama(unsigned int num, const char *dni, Tsublista sig) {
    Tsublista c = (Tsublista)malloc(sizeof(nodosub));
    c->numeroc = num;
    strcpy(c->dni, dni);
    c->sig = sig;
    return c;
}

TLsimple nuevaHab(unsigned int num, char tipo, Tsublista camas, TLsimple sig) {
    TLsimple h = (TLsimple)malloc(sizeof(nodol));
    h->numeroh = num;
    h->tipoh = tipo;
    h->subcamas = camas;
    h->sig = sig;
    return h;
}

void cargaLH(TLsimple *LH) {
    *LH = nuevaHab(99, 'A', NULL,
          nuevaHab(100, 'B', nuevaCama(1, "", NULL),                      /* 1 cama: sirve a eshi */
          nuevaHab(105, 'B', nuevaCama(2, "8888888",
                             nuevaCama(3, "", NULL)),                     /* 2 camas: sirve a nohi */
          nuevaHab(110, 'C', nuevaCama(4, "",
                             nuevaCama(5, "5555555",
                             nuevaCama(6, "", NULL))),
          nuevaHab(201, 'C', NULL, NULL)))));
}


void cargaC(Tcola *C) {
    Telementoc e;
    iniciac(C);

    strcpy(e.documento, "1234567"); strcpy(e.d, "1234567");
    e.htipo='B'; e.habind='S'; e.ingcli='N'; ponec(C, e);   /* eshi -> hab 100 */

    strcpy(e.documento, "2222222"); strcpy(e.d, "2222222");
    e.htipo='B'; e.habind='N'; e.ingcli='N'; ponec(C, e);   /* nohi -> hab 105 cama 3 */

    strcpy(e.documento, "3333333"); strcpy(e.d, "3333333");
    e.htipo='B'; e.habind='S'; e.ingcli='S'; ponec(C, e);   /* no hay lugar -> LDP */

    strcpy(e.documento, "4444444"); strcpy(e.d, "4444444");
    e.htipo='C'; e.habind='N'; e.ingcli='N'; ponec(C, e);   /* nohi -> hab 110 cama 4 */
}

void nohi( TLsimple *LH, Tsublista *auxsub, Telementoc reg)
{   int cumple = 0;
    TLsimple aux;
    aux = *LH;

    while (aux != NULL && !cumple)
    {
        if ( aux->tipoh == reg.htipo && aux->subcamas != NULL)
        { if ( aux->subcamas->sig != NULL)
            { *auxsub = aux->subcamas;

              while(*auxsub != NULL && strcmp((*auxsub)->dni ,"")!=0)
                *auxsub = (*auxsub)->sig;

                cumple = *auxsub != NULL;

            }
        }
        aux = aux->sig;
    }
}

void eshi( TLsimple *LH, Tsublista *auxsub, Telementoc reg)
{   int cumple = 0;
    TLsimple aux;
    aux = *LH;

    while (aux != NULL && !cumple)
    {
        if ( aux->tipoh == reg.htipo && aux->subcamas != NULL)
        { if ( aux->subcamas->sig == NULL && strcmp(aux->subcamas->dni , "")==0)
                *auxsub = aux->subcamas;

            cumple = *auxsub != NULL;

        }
        aux = aux->sig;
    }
}

void insertaLDP(TLdoble *LDP, Telementoc reg)
{   pnodod aux , nuevo = (pnodod) malloc(sizeof(nodod));
    strcpy(nuevo->doc, reg.documento);
    nuevo->htipo = reg.htipo;
    nuevo->indhab = reg.habind;
    nuevo->cling = reg.ingcli;
    nuevo->sig = NULL ; nuevo->ant = NULL;

    if ( LDP->pri == NULL)
    {   LDP->pri = nuevo;
        LDP->ult = nuevo;
    }
    else
    {
        if ( strcmp(LDP->pri->doc, reg.documento) > 0)
        {   LDP->pri->ant = nuevo;
            nuevo->sig = LDP->pri;
            LDP->pri = nuevo;
        }
        else
        { if ( strcmp(LDP->ult->doc, reg.documento) < 0)
            { LDP->ult->sig = nuevo;
              nuevo->ant = LDP->ult;
              LDP->ult = nuevo;
            }
          else
          {   aux = LDP->pri->sig;

              while ( strcmp(aux->doc, reg.documento) < 0)
                  aux = aux->sig;

              aux->ant->sig = nuevo;
              nuevo->ant = aux->ant;
              nuevo->sig = aux;
              aux->ant = nuevo;

            }
          }
    }
}

void eliminaLH(TLsimple *LH , st8 documento, Tsublista auxs)
{   TLsimple aux = *LH;
    Tsublista auxsub;

    while ( aux != NULL)
    {   auxsub = aux->subcamas;

        while (auxsub != NULL && (strcmp(auxsub->dni, documento) != 0 || auxs == auxsub))
        {
            auxsub = auxsub->sig;
        }
        if (auxsub != NULL)
        {
            strcpy(auxsub->dni , "");

        }
        aux = aux->sig;

    }
}

void procesapedidos(TLsimple *LH, TLdoble *LDP, Tcola *C)
{   Telementoc reg;
    Tsublista auxsub;

    while (!vaciac (*C))
    {
        sacac (C, &reg);
        auxsub=NULL;

        if (reg.habind == 'N')
            nohi( LH, &auxsub, reg);

        else
        { eshi( LH, &auxsub, reg);
          if (auxsub == NULL)
            nohi( LH, &auxsub, reg);
        }

        if (auxsub == NULL)
            insertaLDP ( LDP, reg);

        else
        { strcpy( auxsub->dni, reg.documento);
          if ( reg.ingcli == 'N')
              eliminaLH( LH, reg.documento, auxsub);
        }
    }
}

void incrementavec(Tvecreg vectipos[MAX], char tipo)
{   int i = 0;
    while (i < MAX && vectipos[i].tipo != tipo)
        ++i;
    if (i < MAX)
        ++vectipos[i].canti;
}


void eliminahabitaciones(Tvecreg vectipos[MAX], TLsimple *LH,
TLdoble *LDP)
{ TLsimple act = *LH, ant, elim;
  Tsublista actsub;
  Telementoc reg;

  while (act -> numeroh != 100)
    { ant = act;
      act=act->sig;
    }
  while (act!=NULL && act->numeroh>= 100 && act->numeroh<= 200)
    {
      actsub = act -> subcamas;

      while(actsub!=NULL)
        { if (strcmp(actsub -> dni,"" )!= 0)
            { strcpy(reg.documento, actsub->dni);
              reg.htipo = act->tipoh;
              reg.habind=reg.ingcli='N';

              insertaLDP(LDP, reg);
              incrementavec(vectipos, reg.htipo);
            }
          actsub=actsub->sig;
        }

      elim=act;
      act=act->sig;

      ant->sig=act;

      free(elim);
    }
}

void tipomax ( Tvecreg vectipos[MAX], int i, int max, char *tipo)
{
    if ( i >= 0)
    {
        if (vectipos[i].canti > max)
        { max = vectipos[i].canti;
          *tipo = vectipos[i].tipo;
        }

        tipomax( vectipos, i -1, max, tipo);
    }
}
void mostrarVector(Tvecreg vectipos[MAX]) {
    printf("\n--- ESTADO DEL VECTOR DE TIPOS ---\n");
    int i;
    for (i = 0; i < MAX; i++) {
        printf("Tipo: %c | Pacientes a trasladar: %d\n", vectipos[i].tipo, vectipos[i].canti);
    }
    printf("----------------------------------\n");
}

void mostrarLH(TLsimple LH) {
    printf("\n--- ESTADO DE HABITACIONES (LH) ---\n");
    TLsimple aux = LH;
    if (aux == NULL) {
        printf("(La lista de habitaciones esta vacia)\n");
    }
    while (aux != NULL) {
        printf("Habitacion %u (Tipo: %c)\n", aux->numeroh, aux->tipoh);
        Tsublista sub = aux->subcamas;
        if (sub == NULL) {
            printf("  -> Sin camas registradas.\n");
        }
        while (sub != NULL) {
            printf("  -> Cama %u | DNI: '%s'\n", sub->numeroc, sub->dni);
            sub = sub->sig;
        }
        aux = aux->sig;
    }
    printf("-----------------------------------\n");
}

void mostrarLDP(TLdoble *LDP) {
    printf("\n--- ESTADO DE PEDIDOS PENDIENTES (LDP) ---\n");
    pnodod aux = LDP->pri;
    if (aux == NULL) {
        printf("(No hay pedidos pendientes)\n");
    }
    while (aux != NULL) {
        printf("Doc: %s | Tipo pedida: %c | Hab. Ind: %c | Ingreso: %c\n",
               aux->doc, aux->htipo, aux->indhab, aux->cling);
        aux = aux->sig;
    }
    printf("------------------------------------------\n");
}

int main() {
    TLsimple LH;
    TLdoble LDP;
    Tcola C;
    Tvecreg vectipos[MAX];

    // 1. Inicialización y carga de datos
    cargaLH(&LH);
    cargaLD(&LDP);
    cargaC(&C);
    cargavec(vectipos);

    printf("==== ESTADO INICIAL ====\n");
    mostrarLH(LH);
    mostrarLDP(&LDP);
    // Nota: La cola no se muestra porque al leerla se vacía,
    // pero sabemos que tiene el pedido de prueba cargado.

    // 2. Prueba del Inciso A
    printf("\n==== EJECUTANDO PROCESA PEDIDOS (Inciso A) ====\n");
    procesapedidos(&LH, &LDP, &C);

    printf("\nResultados despues de procesar la cola:\n");
    mostrarLH(LH);
    mostrarLDP(&LDP);

    // 3. Prueba del Inciso B
    printf("\n==== EJECUTANDO ELIMINA HABITACIONES (Inciso B) ====\n");
    eliminahabitaciones(vectipos, &LH, &LDP);

    printf("\nResultados despues de eliminar el primer piso:\n");
    mostrarLH(LH);
    mostrarLDP(&LDP);
    mostrarVector(vectipos);

    // 4. Prueba del Inciso C
    printf("\n==== EJECUTANDO TIPO MAX (Inciso C) ====\n");
    int max_pacientes = -1;
    char tipo_habitacion = ' ';
    tipomax(vectipos, MAX - 1, max_pacientes, &tipo_habitacion);

    printf("El tipo de habitacion con mas pacientes a trasladar es: %c\n", tipo_habitacion);

    printf("\nFin del programa.\n");
    return 0;
}
