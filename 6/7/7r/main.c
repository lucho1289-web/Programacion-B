#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef char st10[10];

typedef struct nodolib
{ st10 titulo, autor ;
  int anio;
  struct nodolib *sig;
} nodolib;

typedef struct nodolib *tsublibro;

typedef struct nodoautsoc
{  st10 nombre;
   tsublibro sub;
   struct nodoautsoc *sig;
} nodoautsoc;

typedef struct nodoautsoc * tlista;

void cargalistas(tlista vecaut[MAX],tlista* listasocio);
void menu(tlista vecaut[MAX],tlista * listasocio);
void agregalib(tlista vecaut[MAX], st10 autor,st10 libro, int anio);
void prestamo(tlista vecaut[MAX], tlista listasocio, st10 autor, st10 libro, st10 socio);
void devolucion(tlista vecaut[MAX],tlista listasocio , st10 socio, st10 libro);
void buscaautor( tlista *autores, st10 autor);
void buscalib( tsublibro *ant, tsublibro *act, st10 libro);
void buscasoc( tlista * devuelvesocio , st10 socio);


void cargalistas(tlista vecaut[MAX], tlista* listasocio)
{
    int i;
    tlista nuevo_socio;

    /* 1. Inicializamos el vector de autores vacío */
    for (i = 0; i < MAX; i++)
    {
        vecaut[i] = NULL;
    }

    /* 2. Inicializamos la lista de socios y le precargamos 3 de prueba */
    *listasocio = NULL;

    nuevo_socio = (tlista)malloc(sizeof(nodoautsoc));
    strcpy(nuevo_socio->nombre, "Pedro");
    nuevo_socio->sub = NULL;
    nuevo_socio->sig = *listasocio;
    *listasocio = nuevo_socio;

    nuevo_socio = (tlista)malloc(sizeof(nodoautsoc));
    strcpy(nuevo_socio->nombre, "Maria");
    nuevo_socio->sub = NULL;
    nuevo_socio->sig = *listasocio;
    *listasocio = nuevo_socio;

    nuevo_socio = (tlista)malloc(sizeof(nodoautsoc));
    strcpy(nuevo_socio->nombre, "Juan");
    nuevo_socio->sub = NULL;
    nuevo_socio->sig = *listasocio;
    *listasocio = nuevo_socio;
}
void menu(tlista vecaut[MAX],tlista* listasocio)
{ int x=1, anio;
  st10 autor, libro,socio;
  printf("que desea hacer? \n 1-agregar libro \n 2-prestamo \n 3- devolucion \n , 0- salir \n ");
  scanf("%d", &x);
  while (x!=0)
  {
      printf("ingrese autor \n");
      scanf("%s", autor);
      printf("ingrese libro \n");
      scanf("%s", libro);
      if (x==1)
      { printf ("ingrese anio de edicion \n");
        scanf("%d", &anio);
        agregalib (vecaut, autor, libro, anio);
      }
      else
      {
           printf("ingrese socio \n");
           scanf("%s", socio);
           if (x==2)
           prestamo(vecaut, *listasocio, autor, libro, socio);
           else
           devolucion(vecaut, *listasocio, socio, libro);

      }
      printf("que desea hacer? \n 1-agregar libro \n 2-prestamo \n 3- devolucion \n , 0- salir \n");
      scanf("%d", &x);
  }

}




void agregalib (tlista vecaut[MAX], st10 autor,st10 libro, int anio)
{ int i =autor[0]-'A';
  tlista ant=NULL, act , nuevo ;
  tsublibro nuevosub,antlibro,actlibro;

  nuevosub= (tsublibro) malloc(sizeof(nodolib));
  strcpy (nuevosub->autor, autor);
  strcpy (nuevosub->titulo, libro);
  nuevosub->anio = anio;
nuevosub->sig=NULL;
  act = vecaut[i];

  while (act!=NULL && strcmp(act->nombre, autor) <0)
  { ant=act;
    act=act->sig;
  }

  if (( act==NULL||strcmp(act->nombre, autor) >0 )&& ant == NULL )
  {
     nuevo= (tlista) malloc (sizeof(nodoautsoc));
     strcpy (nuevo->nombre, autor);
     nuevo->sig = vecaut[i];
     vecaut[i]= nuevo;
     nuevo->sub=nuevosub;

  }
  else
  {  if (strcmp(act->nombre, autor) >0)
     {
       nuevo= (tlista) malloc (sizeof(nodoautsoc));
       strcpy (nuevo->nombre, autor);
       nuevo->sig = act;
       ant->sig = nuevo;
       nuevo->sub=nuevosub;
     }

     else
     {
         antlibro=NULL;
         actlibro=act->sub;
         buscalib ( &antlibro, &actlibro, libro);
         if (antlibro==NULL)
         {
             nuevosub->sig=act->sub;
             act->sub=nuevosub;
         }
         else
         {
            nuevosub->sig=actlibro;
            antlibro->sig=nuevosub;
         }
     }
  }

}


void prestamo( tlista vecaut[MAX], tlista listasocio, st10 autor, st10 libro, st10 socio)
{ int i = autor[0] - 'A';
  tlista lautor = vecaut[i] , lsocio;
  tsublibro ants = NULL, acts , subsocio ;
  buscaautor( &lautor, autor);
  if (lautor!= NULL)
  { acts = lautor->sub;
    buscalib( &ants, &acts, libro);
    if (acts!=NULL)
    {
       if (ants == NULL)
          lautor->sub = acts->sig;
       else
          ants->sig = acts->sig;
       lsocio=listasocio;
       buscasoc( &lsocio, socio);
       subsocio= lsocio->sub;
      if (subsocio!=NULL)
      {
          while (subsocio->sig!=NULL)
          subsocio = subsocio->sig;
          subsocio->sig = acts;
      }
        else
            lsocio->sub=acts;
        acts->sig=NULL;
    }
    else
       printf("el libro no esta \n");
  }
  else
       printf("el autor no esta \n");
}

void devolucion( tlista vecaut[MAX], tlista lsocio,st10 socio, st10 libro)
{ int i ;
  tlista  lautor;
  tsublibro antsub=NULL , actsub, actlibro, antlibro=NULL;

  buscasoc( &lsocio, socio);

  actsub= lsocio->sub ;

  while (actsub != NULL && strcmp(actsub->titulo,
  libro)!=0)
  {
    antsub = actsub ;
    actsub = actsub->sig;
  }
  if (actsub !=NULL)
  {
    if (antsub == NULL)
       lsocio->sub = actsub->sig;
    else
       antsub->sig = actsub->sig;
    i=actsub->autor[0]-'A';
    lautor=vecaut[i];
    buscaautor( &lautor, actsub->autor );
       actlibro = lautor->sub;
    if (actlibro!=NULL)
    {
          buscalib ( &antlibro, &actlibro, libro);

        if (antlibro==NULL)
        { actsub->sig = lautor->sub;
          lautor->sub = actsub;
        }
        else
        {
          actsub->sig = actlibro;
          antlibro->sig = actsub ;
        }
    }
    else
    {
        lautor->sub=actsub;
    }

  }
  else
      printf("libro no disponible \n");
}


void buscaautor( tlista *autores, st10 autor)
{

    while(*autores != NULL && strcmp((*autores)->nombre, autor)<0)
      *autores = (*autores)->sig;
}

void buscalib( tsublibro *ant, tsublibro *act, st10 libro)
{
    while( *act != NULL && strcmp((*act)->titulo,libro) < 0)
    { *ant = *act;
      *act = (*act)->sig;
    }
}

void buscasoc( tlista * devuelvesocio , st10 socio)
{
    while ( (*devuelvesocio != NULL )&& strcmp((*devuelvesocio)->nombre, socio) !=0)

    *devuelvesocio = (*devuelvesocio)->sig;
}


int main()
{
    tlista vecaut[MAX],listasocio;

    cargalistas(vecaut,&listasocio);
    menu(vecaut,&listasocio);
    return(0);
}
