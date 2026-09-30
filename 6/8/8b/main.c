#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct nodoc
{ char letra;
  struct nodoc *sig;
} nodoc;

typedef struct nodoc* tlistac;

void cargalista(tlistac * listacaracter);
void muestralista(tlistac listacaracter);
int esvocal(char letra);
int cantvocales(tlistac listacaracter);
int ordenada(tlistac listacaracter);
void elimina(tlistac *listacaracter, int p);

// --- Página 2 ---

void cargalista(tlistac *listacaracter)
{
    char resp;
    tlistac nuevo;

    printf("¿Desea ingresar una letra? (s/n): ");
    scanf(" %c", &resp);

    while (resp == 's' || resp == 'S')
    {
        nuevo = (tlistac)malloc(sizeof(nodoc));
        printf("Ingrese la letra: ");
        scanf(" %c", &nuevo->letra);

        if (*listacaracter == NULL)
        {
            /* Caso Lista Vacía: El nodo apunta a sí mismo */
            nuevo->sig = nuevo;
            *listacaracter = nuevo;
        }
        else
        {
            /* Caso General: Inserción al final de la circular */
            nuevo->sig = (*listacaracter)->sig; /* El nuevo apunta al primero */
            (*listacaracter)->sig = nuevo;      /* El viejo último apunta al nuevo */
            *listacaracter = nuevo;             /* El puntero de la lista se mueve al nuevo último */
        }

        printf("¿Desea ingresar otra letra? (s/n): ");
        scanf(" %c", &resp);
    }
}

void muestralista(tlistac listacaracter)
{ tlistac aux;
  if(listacaracter!=NULL)
  {
      aux=listacaracter->sig;

    while (aux!=listacaracter)
        {printf("%c", aux->letra);
         aux=aux->sig;
        }
    printf("%c", listacaracter->letra);
  }
}

int esvocal (char letra)
{ return( toupper(letra)=='A' || toupper(letra)=='E' || toupper(letra)=='I' ||
  toupper(letra)=='O' || toupper(letra)=='U');
}

int cantvocales (tlistac listacaracter)
{   int cant=0;
    tlistac aux = listacaracter->sig;
    if (listacaracter!=NULL)
    { if (esvocal(listacaracter->letra))
        ++cant;

      while (aux!=listacaracter)
      {
        if (esvocal(aux->letra))
          ++cant;
        aux=aux->sig;
      }

    }
    return(cant);
}


int ordenada(tlistac listacaracter)
{   tlistac aux = listacaracter->sig;

    if (listacaracter!=NULL)
    { if (aux->letra < listacaracter->letra)
        {
            while ( aux!=listacaracter &&
                    aux->letra < aux->sig->letra)

                aux=aux->sig;

            return(aux==listacaracter);
        }
        else
            return (0);
    }
}


void elimina(tlistac *listacaracter, int p)
{   tlistac ant = *listacaracter, act=(*listacaracter)->sig;
    int i=1;

    if (*listacaracter!=NULL)
    {
        while(act != *listacaracter && i<p)
        {   ant=act;
            act=act->sig;
            ++i;
        }

          if (act==*listacaracter)
            {
                if (ant==*listacaracter)
                {
                    *listacaracter=NULL;
                }
                else
                {
                 ant->sig=(*listacaracter)->sig;
                *listacaracter=ant;
                }

            }

            else

                ant->sig = act->sig;
        }

        free(act);
    }



int main()
{
    tlistac listacaracter = NULL; /* Inicialización vital para evitar Segmentation Faults */
    int vocales, orden, pos;

    printf("--- CARGA DE LA LISTA CIRCULAR ---\n");
    cargalista(&listacaracter);

    printf("\n--- CONTENIDO DE LA LISTA ---\n");
    muestralista(listacaracter);

    if (listacaracter != NULL)
    {
        vocales = cantvocales(listacaracter);
        printf("\nCantidad de vocales: %d\n", vocales);

        orden = ordenada(listacaracter);
        if (orden == 1)
            printf("La lista esta ordenada alfabeticamente.\n");
        else
            printf("La lista NO esta ordenada.\n");

        printf("\nIngrese la posicion a eliminar: ");
        scanf("%d", &pos);
        elimina(&listacaracter, pos);

        printf("\n--- LISTA DESPUES DE ELIMINACION ---\n");
        muestralista(listacaracter);
    }
    else
    {
        printf("\nLa lista esta vacia, no hay operaciones para realizar.\n");
    }

    return 0;
}
