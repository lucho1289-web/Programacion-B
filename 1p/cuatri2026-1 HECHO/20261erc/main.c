#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
typedef char st14[15];

/* ==========================================
 *   TDA COLA (Agregado para que compile)
 * ========================================== */
typedef struct {
    int cod;
    st14 fyh;
    int matricula;
} Telementoc;

typedef struct nodoc {
    Telementoc dato;
    struct nodoc *sig;
} nodoc;

typedef struct {
    nodoc *pri, *ult;
} tcola;

typedef tcola Tcola;

void iniciac(tcola *c) {
    c->pri = NULL;
    c->ult = NULL;
}

int vaciac(tcola c) {
    return c.pri == NULL;
}

void ponec(tcola *c, Telementoc reg) {
    nodoc *aux = (nodoc *)malloc(sizeof(nodoc));
    aux->dato = reg;
    aux->sig = NULL;
    if (c->pri == NULL) c->pri = aux;
    else c->ult->sig = aux;
    c->ult = aux;
}

void sacac(tcola *c, Telementoc *reg) {
    nodoc *aux;
    if (c->pri != NULL) {
        aux = c->pri;
        *reg = aux->dato;
        c->pri = c->pri->sig;
        if (c->pri == NULL) c->ult = NULL;
        free(aux);
    }
}



typedef struct nodosub{
    int nromat;
    struct nodosub *sig;
} nodosub;

typedef struct nodosub * tsublista;
typedef tsublista Tsublista;

typedef struct nodolista{
    st14 fyh;
    int cantpresentes;
    tsublista sub;
    struct nodolista *sig;
} nodolista;

typedef struct nodolista * TLsimple;

typedef struct tvec {
    TLsimple L;
    unsigned int cantinscriptos;
} tvec;

typedef struct nodod {
    struct nodod *ant, *sig;
    int cod, cantclases;
    float porc;
} nodod;

typedef struct nodod * pnodod;

typedef struct TLdoble{
    pnodod pri,ult;
} TLdoble;



void cargacola( tcola *c);
void cargavas( tvec VAS[MAX], int N);
void procesac( tvec VAS[MAX], tcola *c);
void corrije( TLsimple *Lk , TLsimple *Lx, st14 DH);
void creoLD( tvec VAS[MAX], TLdoble *LD ,int N);

//LAS FUNCIONES DE CARGA Y TDA ESTAN HECHAS CON IA//
void mostrarVAS(tvec VAS[], int N);
void mostrarLD(TLdoble LD);



void cargacola( tcola *c)
{
    iniciac(c);
    Telementoc e;

    // Cargamos pedidos de prueba automáticos
    // Asignatura 0, Clase 10/10, Matricula 101
    e.cod = 0; strcpy(e.fyh, "10/10"); e.matricula = 101; ponec(c, e);
    // Asignatura 0, Clase 10/10, Matricula 102 (suma a la misma clase)
    e.cod = 0; strcpy(e.fyh, "10/10"); e.matricula = 102; ponec(c, e);

    // Asignatura 1, Clase 15/10, Matricula 201 (clase incorrecta a corregir)
    e.cod = 1; strcpy(e.fyh, "15/10"); e.matricula = 201; ponec(c, e);
    e.cod=2; strcpy(e.fyh,"26-05-10 09:00"); e.matricula=101; ponec(c,e);
    e.cod=2; strcpy(e.fyh,"26-05-12 09:00"); e.matricula=102; ponec(c,e);
    e.cod=2; strcpy(e.fyh,"26-05-08 09:00"); e.matricula=103; ponec(c,e);
    e.cod=2; strcpy(e.fyh,"26-05-10 09:00"); e.matricula=101; ponec(c,e);  /* repetido */
}


void cargavas( tvec VAS[MAX], int N)
{
    int i;
    for (i = 0; i <= N; i++) {
        VAS[i].L = NULL;
        VAS[i].cantinscriptos = 50 + (i * 10);
    }
}

void procesac( tvec VAS[MAX], tcola *c )
{
    Telementoc reg;
    TLsimple ant, act, nuevo ;
    Tsublista actsub, nuevosub, antsub;
    reg.cod = 999 ; strcpy(reg.fyh, "    ");
    ponec(c, reg);
    sacac(c, &reg);
    while( reg.cod != 999)
    {   ant=NULL;
        act = VAS[reg.cod].L ;
        while( act!=NULL && strcmp(act->fyh, reg.fyh)<0)
        {
            ant=act;
            act=act->sig;
        }


        if (act == NULL || strcmp(act->fyh, reg.fyh)!=0)
        {
            nuevo = (TLsimple)malloc(sizeof (nodolista));
            strcpy(nuevo->fyh, reg.fyh);
            nuevo->sub = NULL;
            nuevo->cantpresentes = 0;

            if (ant==NULL)
            {
                nuevo->sig = VAS[reg.cod].L ;
                VAS [reg.cod].L = nuevo ;
            }
            else
            {
                nuevo->sig = ant->sig;
                ant->sig = nuevo;
            }
            act=nuevo;
        }
        actsub=act->sub;



        antsub = NULL;


        while (actsub !=NULL && actsub->nromat != reg.matricula)
        {
            antsub = actsub;
            actsub = actsub->sig;
        }

        nuevosub=(Tsublista)malloc(sizeof (nodosub));
        nuevosub->nromat = reg.matricula ;


        if ( actsub == NULL)
        {
            if (antsub == NULL)
                act->sub = nuevosub;
            else
                antsub->sig = nuevosub;
            nuevosub->sig = NULL;
            ++act->cantpresentes ;
        }
        else
        {
            ponec (c, reg);
            free(nuevosub);
        }
        sacac(c, &reg);
    }
}

void corrije( TLsimple *Lk, TLsimple *Lx, st14 DH)
{
    TLsimple act = *Lx , ant=NULL, nuevo ;

    while( act != NULL && strcmp(act->fyh, DH)!=0)
    {
        ant = act;
        act=act->sig;
    }



    nuevo=act;
    if (ant==NULL)
        *Lx = act->sig;
    else
        ant->sig=act->sig;

    act= *Lk ;
    ant=NULL;

    while ( act!=NULL && strcmp(act->fyh, DH)<0)
    {
        ant=act;
        act=act->sig;
    }

    if (ant==NULL)
    {
        nuevo->sig = *Lk ;
        *Lk = nuevo;
    }
    else
    {
        nuevo->sig = act ;
        ant->sig = nuevo;
    }
}

void creoLD( tvec VAS[MAX], TLdoble *LD ,int N)
{
    TLsimple act;
    pnodod nuevo;
    int cantclases, acumpresentes ,i ;

    for ( i=0; i <= N ; ++i)
    {
        act = VAS[i].L;
        cantclases=0; acumpresentes=0 ;


        while (act!=NULL)
        {
            ++cantclases;
            acumpresentes+= act->cantpresentes;
            act=act->sig;
        }

        if (cantclases!=0)
        {   nuevo = (pnodod)malloc(sizeof (nodod));
            nuevo->cod = i ;
            nuevo->cantclases=cantclases;
            nuevo->porc = 100.0f * acumpresentes / ((float)cantclases * VAS[i].cantinscriptos);
            nuevo->sig=NULL; nuevo->ant=NULL;
            if (LD->ult==NULL)
                LD ->pri=nuevo;
            else
            {
                nuevo->ant = LD->ult;
                LD->ult->sig = nuevo ;
            }
            LD->ult = nuevo;
        }
    }
}

// ===============================================
// FUNCIONES DE MUESTRA PARA COMPROBAR EL RESULTADO
// ===============================================

void mostrarVAS(tvec VAS[], int N) {
    int i;
    printf("\n--- ESTADO DEL VECTOR (ASIGNATURAS) ---\n");
    for(i = 0; i <= N; i++) {
        printf("Asignatura [%d] - Inscriptos: %u\n", i, VAS[i].cantinscriptos);
        TLsimple act = VAS[i].L;
        if (!act) printf("  (Sin clases registradas)\n");
        while(act != NULL) {
            printf("  Clase Fecha: %s | Presentes en total: %d\n", act->fyh, act->cantpresentes);
            tsublista sub = act->sub;
            while(sub != NULL) {
                printf("    -> Asistencia Matricula Nro: %d\n", sub->nromat);
                sub = sub->sig;
            }
            act = act->sig;
        }
    }
    printf("---------------------------------------\n");
}

void mostrarLD(TLdoble LD) {
    printf("\n--- ESTADO DE LA LISTA DOBLE (RESUMEN) ---\n");
    pnodod act = LD.pri;
    if (act == NULL) printf("(Lista doble vacia)\n");
    while(act != NULL) {
        printf("Asignatura Cod: %d | Clases dictadas: %d | ... Porcentaje: %.2f\n", act->cod, act->cantclases, act->porc);
        act = act->sig;
    }
    printf("------------------------------------------\n");
}



int main()
{
    tvec VAS[MAX];
    TLdoble LD ;
    Tcola c ;
    int k, x, N ;
    st14 DH ;

    LD.pri=NULL;
    LD.ult=NULL;


    printf("==== SIMULACION AUTOMATICA ====\n");
    N = 2;
    cargacola(&c);
    cargavas(VAS, N);
    printf("Carga finalizada con datos de prueba.\n");

    procesac (VAS, &c);
    mostrarVAS(VAS, N);


    printf("\nVamos a mover la clase '15/10' de la Asignatura 1 a la Asignatura 0.\n");


    k = 0;
    x = 1;
    strcpy(DH, "15/10");

    corrije (&VAS[k].L, &VAS[x].L, DH);

    printf("\n DESPUES DE USAR CORRIJE \n");
    mostrarVAS(VAS, N);


    creoLD( VAS, &LD, N);
    mostrarLD(LD);

    return(0);
}
